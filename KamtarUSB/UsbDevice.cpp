/*
 * UsbDevice.cpp
 *
 *  Created on: 18 Mar 2021
 *      Author: Kamtar
 */

#include <usb/UsbDevice.hpp>

namespace KamtarUSB {

UsbDevice::UsbDevice()
{
	if(s_created)
		return;

	s_ep_len = 0;
	s_init = false;
	s_created = true;
}

void UsbDevice::Init()
{
	if(s_init == true)
		return;

	if( USB_DeviceInit(2, (usb_device_callback_t)s_device_callback, &s_dev_ptr)  != kStatus_USB_Success)
	{
		assert(false);
		return;
	}

	s_init = true;
}

void UsbDevice::InitBaseClass()
{
	 s_instance_list[s_instance_num]._m = this;
	 s_instance_list[s_instance_num].dev = this;
	 s_instance_num++;
}

void UsbDevice::register_control_handler (UsbDevice& dev)
{
	s_control_handler = &dev;
}

bool UsbDevice::init_endpoint(usb_device_endpoint_init_struct_t& ep)
{
	for(int i=0; i<s_ep_len; i++)
	{
		if(s_ep_list[i].e_addr == ep.endpointAddress)
		{
			assert(false);
			return false;
		}
	}

	s_ep_list[s_ep_len].magic = 0xBEEF;
	s_ep_list[s_ep_len].e_addr = ep.endpointAddress;
	s_ep_list[s_ep_len]._m = this;


	usb_device_endpoint_callback_struct_t epCallback;
    epCallback.callbackFn = s_endpoint_callback;
    epCallback.callbackParam = &s_ep_list[s_ep_len];

    s_ep_len++;

    return kStatus_USB_Success == USB_DeviceInitEndpoint(s_dev_ptr, &ep, &epCallback);
}

usb_status_t UsbDevice::s_device_callback(usb_device_handle handle, uint32_t callbackEvent, void *eventParam)
{
	switch (callbackEvent)
	{
	case kUSB_DeviceEventBusReset:
		s_ep_len = 0;
		usb_echo("USB: BusReset\r\n");
		for(int i=0; i<s_instance_num; i++)
			 s_instance_list[i]._m->InitClass();
		break;
	default:
		assert(false);
		break;
	}

	return kStatus_USB_Success;
}

usb_status_t UsbDevice::s_endpoint_callback(usb_device_handle handle,  usb_device_endpoint_callback_message_struct_t *message, void *callbackParam)
{
	endpoint_entry* e_entry = (endpoint_entry*)callbackParam;

	if(e_entry->magic != 0xBEEF)
	{
		assert(false);
		return kStatus_USB_Error;
	}

	return e_entry->_m->endpoint_callback(handle, message, e_entry->e_addr);
}
}/* namespace KamtarUSB */
