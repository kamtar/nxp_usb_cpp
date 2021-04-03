/*
 * USBManager.hpp
 *
 *  Created on: 27 Feb 2021
 *      Author: Kamtar
 */

#ifndef SOURCE_USBMANAGER_HPP_
#define SOURCE_USBMANAGER_HPP_
#include <usb/usb_misc.hpp>
#include <stdint.h>


#include "usb_device_config.h"
#include "usb.h"

#include "usb_device.h"
#include "usb_device_dci.h"

#include "fsl_device_registers.h"

#include "usb_device_ehci.h"

using namespace KamtarUSB;

class USBManager
{
	constexpr static size_t DescriptorListMax = 8;
	constexpr static size_t StringListLen = 3;
	constexpr static size_t LanguageLen = 1;

	constexpr static uint8_t VendorNameIndex = 1;
	constexpr static uint8_t DeviceNameIndex = 2;

public:
	static void Init(uint8_t usb_id);

	static bool register_Descriptor(uint8_t* data, size_t len, uint8_t cfg_num = 0);
	static bool init_USB();

	static void SetVendorString(const char* str);
	static void SetDeviceString(const char* str);

	//Get descriptors callback - should be called from Chapter9 stack
	static usb_status_t USB_DeviceGetDescriptor(usb_device_handle handle, usb_setup_struct_t *setup, uint32_t *out_length, uint8_t **out_buffer);

private:

	inline static uint8_t s_usb_id;
	inline static uint8_t s_list_n;
	inline static DescriptorItem s_desc_list[DescriptorListMax];

	inline USB_DMA_INIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static DeviceDesc s_dev_desc;

	inline USB_DMA_INIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static uint8_t s_string0[4] = {4, (uint8_t)DescType::String, 0x09, 0x04};

	inline USB_DMA_INIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static uint8_t s_VendorString[64];
	inline USB_DMA_INIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static uint8_t s_DeviceString[64];

	inline USB_DMA_INIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE) static uint8_t s_ConfigDestriptors[208];
	inline static uint8_t s_ConfigDescLen;

};



#endif /* SOURCE_USBMANAGER_HPP_ */
