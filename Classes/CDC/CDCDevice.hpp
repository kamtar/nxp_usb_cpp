/*
 * CDCDevice.hpp
 *
 *  Created on: 3 Apr 2021
 *      Author: Kamtar
 */

#ifndef USB_CDCDEVICE_HPP_
#define USB_CDCDEVICE_HPP_
#include "../../UsbDevice.hpp"

namespace KamtarUSB {

class CDCDevice : public UsbDevice  {
public:

	struct CDCSerialDesc
	{
		InterfaceDesc	cdc_if;
		uint8_t lazy_class_specific_data[19];
		EndpointDesc notification_ep;
		InterfaceDesc data_if;
		EndpointDesc bulkin_ep;
		EndpointDesc bulkout_ep;
		static void Defaults(CDCSerialDesc &d)
		{
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

	virtual DescriptorItem GetCfgDescriptors() override { return DescriptorItem {.data = &m_desc, .len=sizeof(CDCSerialDesc), .cfg_id=m_cfg_id, .if_num = 2};	};

private:
	CDCSerialDesc m_desc;
	uint8_t m_cfg_id;
};

} /* namespace KamtarUSB */

#endif /* USB_CDCDEVICE_HPP_ */
