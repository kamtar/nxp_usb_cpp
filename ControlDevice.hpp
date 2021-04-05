/*
 * ControlDevice.hpp
 *
 *  Created on: 2 Apr 2021
 *      Author: Kamtar
 */

#ifndef LIB_CPP_USB_CONTROLDEVICE_HPP_
#define LIB_CPP_USB_CONTROLDEVICE_HPP_
#include "./UsbDevice.hpp"

namespace KamtarUSB {

class ControlDevice : public UsbDevice {

public:
	enum class UsbStRq : uint8_t{
		SetAddr = 5,
		GetDescriptor = 6
	};
	ControlDevice();

	virtual void InitClass() override;
	virtual usb_status_t device_callback(usb_device_handle handle, uint32_t callbackEvent, void *eventParam) override;

	virtual usb_status_t endpoint_callback(usb_device_handle handle,  usb_device_endpoint_callback_message_struct_t *message, uint8_t ep) override;

	virtual DescriptorItem GetCfgDescriptors() override { return DescriptorItem {.data = &s_cfg_desc, .len = sizeof(ConfigurationDesc), .if_num=0};	};

	ConfigurationDesc s_cfg_desc;
private:
	void setup_control_ep();

	usb_setup_struct_t m_setup_buff;
	uint8_t num = 0;
};

} /* namespace KamtarUSB */

#endif /* LIB_CPP_USB_CONTROLDEVICE_HPP_ */
