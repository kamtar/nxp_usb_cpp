/*
 * ControlDevice.cpp
 *
 *  Created on: 2 Apr 2021
 *      Author: Kamtar
 */

#include <usb/ControlDevice.hpp>
#include <usb_device_ch9.h>

namespace KamtarUSB {

ControlDevice::ControlDevice()
{
	// TODO Auto-generated constructor stub
	InitBaseClass();
}

void ControlDevice::InitClass()
{

	setup_control_ep();
}

void ControlDevice::setup_control_ep()
{
	usb_device_endpoint_init_struct_t ep;

	ep.zlt = 1;
	ep.transferType = USB_ENDPOINT_CONTROL;
	ep.interval = 0;
	ep.endpointAddress = USB_CONTROL_ENDPOINT | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT);
	ep.maxPacketSize = 64;

	if(init_endpoint(ep) == false) assert(false);

	ep.endpointAddress = USB_CONTROL_ENDPOINT | (USB_OUT << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT);

	if(init_endpoint(ep) == false) assert(false);
}

usb_status_t ControlDevice::endpoint_callback(usb_device_handle handle,  usb_device_endpoint_callback_message_struct_t *message, uint8_t ep)
{

	 uint8_t* buffer_ptr = 0;
	 uint32_t buffer_len = 0;
	 usb_status_t ret = kStatus_USB_InvalidRequest;

	if (message->isSetup)
	{
		usb_setup_struct_t *setup = (usb_setup_struct_t *)(message->buffer);

		switch((UsbStRq)setup->bRequest)
		{
		case UsbStRq::SetAddr:
			usb_echo("USB: SET_ADDR: %d\r\n", setup->wValue);
			USB_DeviceSetStatus(handle, kUSB_DeviceStatusAddress, &setup->wValue);
			buffer_len = 0;
			//send ACK:
			ret = USB_DeviceSendRequest(handle, 0, buffer_ptr, buffer_len);
			break;

		case UsbStRq::GetDescriptor:
			ret = USBManager::USB_DeviceGetDescriptor(handle, setup, &buffer_len, &buffer_ptr);

			if(kStatus_USB_Success == ret)
			{
				ret = USB_DeviceSendRequest(handle, 0, buffer_ptr, buffer_len);
				//Prime endpoint to receive ACK from host
				if ((kStatus_USB_Success == ret) && (USB_REQUEST_TYPE_DIR_IN == (setup->bmRequestType & USB_REQUEST_TYPE_DIR_MASK)))
					ret = USB_DeviceRecvRequest(handle, 0, (uint8_t *)nullptr, 0);
			}
			else
			{
				usb_echo("USB: Unkwown descriptor id");
				assert(false);
			}
			break;

		default:
			usb_echo("USB: Unhandled setup rq - %d \r\n", setup->bRequest);
			break;
		}
	}else
	{
		usb_echo("USB: NON-SETUP unhandled rq\r\n");
	}


	return ret;
}

usb_status_t ControlDevice::device_callback(usb_device_handle handle, uint32_t callbackEvent, void *eventParam)
{
	return kStatus_USB_InvalidRequest;
}

} /* namespace KamtarUSB */
