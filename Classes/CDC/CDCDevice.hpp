/*
 * CDCDevice.hpp
 *
 *  Created on: 3 Apr 2021
 *      Author: Kamtar
 */

#ifndef USB_CDCDEVICE_HPP_
#define USB_CDCDEVICE_HPP_
#include <usb/UsbDevice.hpp>

namespace KamtarUSB {

class CDCDevice : public UsbDevice  {
public:

	struct CDCSerialDesc
	{
		ConfigurationDesc cfg;
		InterfaceDesc	cdc_if;
		uint8_t lazy_class_specific_data[19];
		EndpointDesc notification_ep;
		InterfaceDesc data_if;
		EndpointDesc bulkin_ep;
		EndpointDesc bulkout_ep;
		static void Defaults(CDCSerialDesc &d)
		{
			ConfigurationDesc::Defaults(d.cfg);
			InterfaceDesc::Defaults(d.cdc_if);
			EndpointDesc::Defaults(d.notification_ep);
			InterfaceDesc::Defaults(d.data_if);
			EndpointDesc::Defaults(d.bulkin_ep);
			EndpointDesc::Defaults(d.bulkout_ep);
		}
	} PACKED;

	CDCDevice(uint8_t config_id);

	virtual void InitClass() override;

	virtual usb_status_t device_callback(usb_device_handle handle, uint32_t callbackEvent, void *eventParam) override;

	virtual usb_status_t endpoint_callback(usb_device_handle handle,  usb_device_endpoint_callback_message_struct_t *message, uint8_t ep) override;

private:
	CDCSerialDesc m_desc;
};

} /* namespace KamtarUSB */

#endif /* USB_CDCDEVICE_HPP_ */
