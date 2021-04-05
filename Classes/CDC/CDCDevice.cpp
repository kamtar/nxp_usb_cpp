/*
 * CDCDevice.cpp
 *
 *  Created on: 3 Apr 2021
 *      Author: Kamtar
 */

#include "./CDCDevice.hpp"
#include <usb_device_descriptor.h>
namespace KamtarUSB {

CDCDevice::CDCDevice(uint8_t config_id)
{
	CDCSerialDesc::Defaults(m_desc);


	m_desc.cdc_if.bInterfaceNumber = 0;
	m_desc.cdc_if.bAlternateSetting = 0;
	m_desc.cdc_if.bNumEndpoints = 1;
	m_desc.cdc_if.bInterfaceClass = 2;
	m_desc.cdc_if.bInterfaceSubClass = 2;
	m_desc.cdc_if.bInterfaceProtocol = 0;
	m_desc.cdc_if.iInterface = 0;

	uint8_t arr[19] = {    /* CDC Class-Specific descriptor */
		    USB_DESCRIPTOR_LENGTH_CDC_HEADER_FUNC, /* Size of this descriptor in bytes */
		    USB_DESCRIPTOR_TYPE_CDC_CS_INTERFACE,  /* CS_INTERFACE Descriptor Type */
		    USB_CDC_HEADER_FUNC_DESC, 0x10,
		    0x01, /* USB Class Definitions for Communications the Communication specification version 1.10 */

		    USB_DESCRIPTOR_LENGTH_CDC_CALL_MANAG, /* Size of this descriptor in bytes */
		    USB_DESCRIPTOR_TYPE_CDC_CS_INTERFACE, /* CS_INTERFACE Descriptor Type */
		    USB_CDC_CALL_MANAGEMENT_FUNC_DESC,
		    0x01, /*Bit 0: Whether device handle call management itself 1, Bit 1: Whether device can send/receive call
		             management information over a Data Class Interface 0 */
		    0x01, /* Indicates multiplexed commands are handled via data interface */

		    USB_DESCRIPTOR_LENGTH_CDC_ABSTRACT,   /* Size of this descriptor in bytes */
		    USB_DESCRIPTOR_TYPE_CDC_CS_INTERFACE, /* CS_INTERFACE Descriptor Type */
		    USB_CDC_ABSTRACT_CONTROL_FUNC_DESC,
		    0x06, /* Bit 0: Whether device supports the request combination of Set_Comm_Feature, Clear_Comm_Feature, and
		             Get_Comm_Feature 0, Bit 1: Whether device supports the request combination of Set_Line_Coding,
		             Set_Control_Line_State, Get_Line_Coding, and the notification Serial_State 1, Bit ...  */

		    USB_DESCRIPTOR_LENGTH_CDC_UNION_FUNC, /* Size of this descriptor in bytes */
		    USB_DESCRIPTOR_TYPE_CDC_CS_INTERFACE, /* CS_INTERFACE Descriptor Type */
		    USB_CDC_UNION_FUNC_DESC, 0x00,        /* The interface number of the Communications or Data Class interface  */
		    0x01                                 /* Interface number of subordinate interface in the Union  */
	};
	for(int i=0; i<19;i++)
		m_desc.lazy_class_specific_data[i] = arr[i];

	m_desc.notification_ep.bEndpointAddress =  1 | (USB_IN << 7U);
	m_desc.notification_ep.bmAttributes = USB_ENDPOINT_INTERRUPT;
	m_desc.notification_ep.wMaxPacketSize = 16;
	m_desc.notification_ep.bInterval = FS_CDC_VCOM_INTERRUPT_IN_INTERVAL;

	m_desc.data_if.bInterfaceNumber = 1;
	m_desc.data_if.bAlternateSetting = 0;
	m_desc.data_if.bNumEndpoints = 2;
	m_desc.data_if.bInterfaceClass = 0x0A;
	m_desc.data_if.bInterfaceSubClass = 0;
	m_desc.data_if.bInterfaceProtocol = 0;
	m_desc.data_if.iInterface = 0;

	m_desc.bulkin_ep.bEndpointAddress = 2 | (USB_IN << 7U);
	m_desc.bulkin_ep.bmAttributes = USB_ENDPOINT_BULK;
	m_desc.bulkin_ep.wMaxPacketSize = 64;
	m_desc.bulkin_ep.bInterval = 0x00;

	m_desc.bulkout_ep.bEndpointAddress = 3 | (USB_OUT << 7U);
	m_desc.bulkout_ep.bmAttributes = USB_ENDPOINT_BULK;
	m_desc.bulkout_ep.wMaxPacketSize = 64;
	m_desc.bulkout_ep.bInterval = 0x00;

	InitBaseClass();
}

void CDCDevice::InitClass()
{

}

 usb_status_t CDCDevice::device_callback(usb_device_handle handle, uint32_t callbackEvent, void *eventParam)
 {
	 return kStatus_USB_InvalidRequest;
 }

 usb_status_t CDCDevice::endpoint_callback(usb_device_handle handle,  usb_device_endpoint_callback_message_struct_t *message, uint8_t ep)
 {
	 return kStatus_USB_InvalidRequest;
 }

} /* namespace KamtarUSB */
