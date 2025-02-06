## ESP32-S3 WIFI SCAN 


This project demonstrates how to scan wifi using the **ESP-IDF** framework on an **ESP32-S3** development board. 💻


## Requirements 📦

- **ESP32-S3** development board 🧑‍💻
- **ESP-IDF** development environment (follow the [ESP-IDF setup guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/)) 🌐
- **Serial Monitor** to view logs 📲

### 1. Configure the Project ⚙️

Run the following command to configure your ESP32-S3 project settings:

```bash
idf.py menuconfig
```

Open the project configuration menu (idf.py menuconfig).


### 2. Build the Project 🛠️

Compile the project using the following command:

```bash
idf.py build
```

### 3. Flash the ESP32-S3 🦸‍♂️

Once the build completes successfully, flash the firmware to your ESP32-S3 board:

```bash
idf.py -p (YOUR PORT) flash
```

### 4. Monitor the Logs 📡

After flashing, monitor the serial output to see the logs. Run:

```bash
idf.py -p (YOUR PORT) monitor
```

You should see the following output in your serial monitor:

```
I (1000) MAIN: LED Blink Example Initialized 🚀
```

## 📜 Project Structure

Here’s an overview of the project structure:

```
/project
   /main                # Contains the main application code
     CMakeLists.txt
     main.c             # Main application file
     idf_component.yml
     Kconfig.projbuild

     inc
        main.h             # Header file for the main application
   /components          # Custom components (if any)
   CMakeLists.txt       # CMake configuration for the project
   sdkconfig    # Configuration file created after setup
   README.md            # This file
```
---

## WIFI in ESP32

Before learning how to scan the wifi in esp32s3 you should learn how to about the wifi in esp32

- ## **ESP32 Wi-Fi Feature List**

The following features are supported:

## **ESP32 Wi-Fi Feature List**

The following features are supported:

- [4 virtual Wi-Fi interfaces](#virtual-wifi-interfaces), which are STA, AP, Sniffer, and reserved.

- [Station-only mode, AP-only mode, station/AP-coexistence mode](#wifi-modes)

- [IEEE 802.11b, IEEE 802.11g, IEEE 802.11n, and APIs to configure the protocol mode](#wifi-standards)

- [WPA/WPA2/WPA3/WPA2-Enterprise/WPA3-Enterprise/WAPI/WPS and DPP](#security-protocols)

- [AMSDU, AMPDU, HT40, QoS, and other key features](#advanced-wifi-features)

- [Modem-sleep](#power-management)

- [The Espressif-specific ESP-NOW protocol and Long Range mode](#custom-protocols), which supports up to 1 km of data traffic

- [Up to 20 MBit/s TCP throughput and 30 MBit/s UDP throughput over the air](#throughput)

- [Sniffer](#wifi-sniffer)

- [Both fast scan and all-channel scan](#scanning)

- [Multiple antennas](#multiple-antennas)

- [Channel state information](#channel-state-information)

- [Wi-Fi Aware (NAN)](#wifi-aware)


---




## Virtual Wi-Fi Interfaces


The ESP32 supports **4 virtual Wi-Fi interfaces** that provide flexibility for various Wi-Fi-related tasks. These interfaces allow the device to perform multiple functions, either simultaneously or in different modes, depending on the application. Here’s a detailed explanation of each of these virtual interfaces:

---

#### 1. **STA (Station) Mode**
   - **STA (Station)** mode allows the ESP32 to **connect to an existing Wi-Fi network** as a client. In this mode, the ESP32 acts like any other device (such as a phone, laptop, or tablet) that connects to an access point (AP).
   
   - **Key Features**:
     - **Client Mode**: ESP32 connects to a Wi-Fi network (a router or any other access point).
     - It can communicate with other devices in the network and access the internet.
     - When in **STA mode**, the ESP32 typically uses DHCP to automatically get an IP address from the AP.
   
   - **Use Cases**:
     - Connecting the ESP32 to an internet router to access online services.
     - Connecting to an existing IoT network to collect data or control devices.

---

#### 2. **AP (Access Point) Mode**
   - **AP (Access Point)** mode turns the ESP32 into a **Wi-Fi access point**. In this mode, the ESP32 creates its own Wi-Fi network, and other devices (like laptops, smartphones, or other ESP32s) can connect to it.
   
   - **Key Features**:
     - The ESP32 acts as the **central hub** for communication with other devices.
     - Devices can join this network to communicate with the ESP32 and each other.
     - Typically, when operating in AP mode, the ESP32 provides a **DHCP server** to allocate IP addresses to connected devices.
     - The ESP32 can be configured to provide **basic security** (WPA2, WPA3) for the network.

   - **Use Cases**:
     - Creating a local network to allow devices to interact with each other, e.g., in a smart home or a local IoT network.
     - Setting up a network where other devices can communicate directly with the ESP32, such as a sensor hub or data collection point.
   
---

#### 3. **Sniffer Mode**
   - **Sniffer mode** turns the ESP32 into a **passive Wi-Fi monitoring device**. When in this mode, the ESP32 listens to the Wi-Fi traffic on the air and **captures packets** without participating in the network (i.e., it does not transmit or receive data on behalf of any network).

   - **Key Features**:
     - The ESP32 **captures all Wi-Fi traffic** it can hear on the wireless channel, including management frames, data frames, and control frames.
     - It does **not interfere** with the network communication, as it is only in listening mode.
     - The captured data can include information such as SSIDs, BSSIDs (MAC addresses), signal strength, and other network parameters.
     - Useful for **network analysis** or **security monitoring**.

   - **Use Cases**:
     - **Wi-Fi network monitoring**: For example, monitoring the health of Wi-Fi networks or analyzing signal strength in a given area.
     - **Security testing**: Can be used to capture packets for **penetration testing** or **network security audits** (e.g., to check for weak or open networks).
     - **Wi-Fi troubleshooting**: Diagnosing connectivity issues or identifying interference sources in a network.
   
   - **Note**: Sniffer mode is **passive**; it only listens and doesn’t actively send or receive data. However, it may be subject to legal regulations in some regions, as it involves intercepting wireless communications.

---

#### 4. **Reserved Mode**
   - The **reserved** mode is a **placeholder** for future use or specific internal purposes within the ESP32 software stack. It is not used for typical Wi-Fi operations and is often **not exposed** to the developer unless specifically required by the ESP32 firmware or a custom application.

   Future Features: Espressif, the company that makes ESP32, might use this mode in the future to add new features or updates to the chip, but for now, it’s just reserved.

   - **Key Features**:
     - This mode is reserved for internal use by the system or for potential future features.
     - It is not typically user-configurable, and you do not interact with it directly in most applications.

   - **Use Cases**:
     - **Internal operations**: Used internally within the ESP32 firmware for tasks that don’t require direct interaction with the user.
     - **Future functionalities**: Espressif (the manufacturer) may allocate this interface to new or advanced Wi-Fi features in future firmware updates.

---

### **Why are these Virtual Interfaces Important?**

The ESP32’s ability to switch between these different modes is a core feature that provides flexibility and versatility. Here’s why:

- **Multiple modes of operation**: The ESP32 can be used as a Wi-Fi client (STA mode), a Wi-Fi access point (AP mode), or a Wi-Fi monitor (Sniffer mode), depending on your application.
- **Simultaneous support for multiple tasks**: With its ability to handle multiple virtual interfaces, the ESP32 can support scenarios where it acts as both a **station and access point simultaneously** (Station/AP coexistence), allowing for more complex network setups.
- **Customizable networking**: Developers can customize the ESP32’s role in a network, using different interfaces as needed, such as turning it into a **Wi-Fi sniffer** for security audits or using **STA mode** to connect to the internet.

---

### **Conclusion:**
The **4 virtual Wi-Fi interfaces** of the ESP32 (STA, AP, Sniffer, and Reserved) give the device great flexibility in terms of connectivity and functionality. Whether you're setting up a simple Wi-Fi client, creating a local Wi-Fi network, capturing Wi-Fi traffic, or using future features, these modes provide a comprehensive suite of networking options.

---


## Wi-Fi Modes

The ESP32 has several operating modes that determine how it connects to Wi-Fi networks. Three key modes are **Station-only mode**, **AP-only mode**, and **Station/AP-coexistence mode**. Here’s a detailed breakdown of each:

---

#### 1. **Station-only Mode (STA Mode)**

In **Station-only mode**, the ESP32 is **only a client device** that connects to an existing Wi-Fi network (usually a router or another access point). It cannot act as an access point itself.

- **How It Works**:
  - The ESP32 connects to a Wi-Fi network in the same way a laptop or smartphone would.
  - The ESP32 sends requests to connect to a Wi-Fi access point (AP), and once connected, it can communicate with other devices on the network, access the internet, or exchange data with other devices on the same network.
  
- **Key Features**:
  - **Client Mode**: The ESP32 is only connecting to other networks; it doesn’t provide a network for other devices to join.
  - It typically uses **DHCP** (Dynamic Host Configuration Protocol) to automatically receive an IP address from the AP.
  - The ESP32 can interact with other devices in the network but doesn’t provide any network service for others.
  
- **Use Cases**:
  - **IoT devices** that connect to the internet (e.g., smart sensors that send data to the cloud).
  - Devices that need internet access but don’t need to create their own Wi-Fi network.
  - **Personal projects** where the ESP32 acts as a client on a home or office Wi-Fi network.

---

#### 2. **AP-only Mode (Access Point Mode)**

In **AP-only mode**, the ESP32 **acts as a Wi-Fi access point**. This means that instead of connecting to an existing Wi-Fi network, it **creates its own Wi-Fi network**, and other devices can connect to it.

- **How It Works**:
  - The ESP32 **creates its own Wi-Fi network**, similar to how your home router works.
  - Other devices, such as smartphones, laptops, or other ESP32 devices, can **connect to the ESP32** as if it were a regular router or access point.
  - You can set up security (WPA2, WPA3) on the ESP32 network to control who connects to it.

- **Key Features**:
  - **Hotspot Mode**: The ESP32 becomes the center of a local Wi-Fi network.
  - It acts as a **DHCP server** and assigns IP addresses to the devices that connect to it.
  - Other devices can communicate with the ESP32 directly and use it for local networking, file sharing, or other tasks.
  
- **Use Cases**:
  - **Local networks** where you don’t need internet access but want devices to communicate (e.g., an IoT device network).
  - **Devices that need to create their own network** for configuration or control (e.g., smart home devices or sensors).
  - **Setting up a Wi-Fi network** in remote areas where there’s no router (like in temporary setups for demonstrations, events, or fieldwork).

---

#### 3. **Station/AP-Coexistence Mode (STA/AP Mode)**

In **Station/AP-coexistence mode**, the ESP32 **acts as both a Station (client)** and **an Access Point (AP)** at the same time. This mode allows it to **connect to another network** (as a client) **while also creating its own network** (as an access point) for other devices to join.

- **How It Works**:
  - The ESP32 connects to a Wi-Fi network (like in Station-only mode) while simultaneously **broadcasting its own network** that other devices can connect to.
  - The ESP32 can **communicate with devices on its own network** (the one it is creating as an AP) while also connecting to external devices over the internet or another network (via its STA connection).
  
- **Key Features**:
  - **Dual Role**: The ESP32 serves dual functions at once—acting as both a **Wi-Fi client** (STA) and a **Wi-Fi hotspot** (AP).
  - Devices that connect to the ESP32’s access point can **communicate directly with it**, while the ESP32 can still **connect to the internet** or other networks using its STA connection.
  - Can be configured to handle **both incoming and outgoing connections** at the same time.
  
- **Use Cases**:
  - **Devices that need internet access but also want to create a local network** for other devices to connect to. For example, a device that needs to upload data to a server but also allows nearby devices to interact with it.
  - **Smart home hubs** that connect to the internet and provide a network for other devices (e.g., creating a mesh network).
  - **Field devices** that gather data from local sensors but also need to upload this data to a central server via the internet.
  - **Wi-Fi Repeaters**: The ESP32 could be used as a repeater that connects to an existing Wi-Fi network while also offering its own local network to nearby devices.

---

### **Comparison of the Three Modes**

| **Feature**                   | **Station-only Mode (STA)**                          | **AP-only Mode (AP)**                               | **Station/AP-Coexistence Mode (STA/AP)**        |
|-------------------------------|------------------------------------------------------|----------------------------------------------------|-------------------------------------------------|
| **Role**                       | Client (connects to an existing Wi-Fi network)       | Host (creates a Wi-Fi network for others to join)  | Both Client and Host (connects to a network and creates its own) |
| **Network Type**               | Joins a network (like your home router)              | Creates a network (like a router)                  | Both joins a network and creates its own        |
| **Devices Connecting**         | Other devices connect to an external Wi-Fi network   | Other devices connect to the ESP32’s network       | Devices can connect to the ESP32’s network and/or to an external Wi-Fi network |
| **Internet Access**            | Yes, can access the internet through an AP           | No, unless connected to another internet source    | Yes, can access the internet through STA, while also providing local network access via AP |
| **Use Cases**                  | IoT devices, smart sensors connecting to Wi-Fi      | Local network for devices, smart home hubs         | IoT hubs, devices requiring local networks and internet access simultaneously |

---


### Wi-Fi Standards
### **IEEE 802.11b, IEEE 802.11g, IEEE 802.11n, and APIs for Protocol Mode Configuration on ESP32**

The **IEEE 802.11** family defines a set of standards for **Wi-Fi** communication, and the ESP32 supports various versions of these standards. The main standards include **802.11b**, **802.11g**, and **802.11n**. Each of these has different performance characteristics, including speed, range, and compatibility.

### **Overview of IEEE 802.11 Standards**

#### **1. IEEE 802.11b (Wi-Fi Standard)**

- **Release Year**: 1999
- **Frequency Band**: **2.4 GHz**
- **Maximum Data Rate**: **11 Mbps**
  
**IEEE 802.11b** is one of the earliest Wi-Fi standards. It operates in the **2.4 GHz** frequency band, which is commonly used by many Wi-Fi devices. 

- **Key Features**:
  - **Maximum Data Rate**: Up to **11 Mbps**.
  - **Modulation**: It uses **DSSS (Direct Sequence Spread Spectrum)** for modulation, which allows devices to operate effectively in environments with noise.
  - **Range**: Generally, the range is decent, but performance degrades with high interference or when there are physical obstructions.
  - **Compatibility**: Most legacy devices support **802.11b**.

- **Use Cases**:
  - **Legacy Devices**: Older devices still rely on 802.11b for basic Wi-Fi connectivity.
  - **Low-Data-Rate Applications**: Applications where high speed is not essential, like IoT devices transmitting small packets of data.

---

#### **2. IEEE 802.11g (Wi-Fi Standard)**

- **Release Year**: 2003
- **Frequency Band**: **2.4 GHz**
- **Maximum Data Rate**: **54 Mbps**

**IEEE 802.11g** is an improvement over 802.11b. It provides faster speeds and more efficient communication, still using the **2.4 GHz** band.

- **Key Features**:
  - **Maximum Data Rate**: Up to **54 Mbps**.
  - **Modulation**: It uses **OFDM (Orthogonal Frequency Division Multiplexing)**, which is more efficient than DSSS (used in 802.11b).
  - **Backward Compatibility**: It is backward compatible with 802.11b, meaning devices that support 802.11g can still communicate with 802.11b devices at slower speeds.
  - **Range**: Similar range to 802.11b, though with better performance and less interference due to OFDM.

- **Use Cases**:
  - **Home Networks**: Popular for home Wi-Fi networks when the primary need is reasonable speed with good compatibility.
  - **Internet of Things (IoT)**: Used in devices that don’t require high throughput but benefit from faster speeds than 802.11b.

---

#### **3. IEEE 802.11n (Wi-Fi Standard)**

- **Release Year**: 2009
- **Frequency Bands**: **2.4 GHz** and **5 GHz** (dual-band)
- **Maximum Data Rate**: **600 Mbps**

**IEEE 802.11n** significantly improves upon 802.11g, supporting both **2.4 GHz and 5 GHz** frequency bands. This allows for **faster speeds**, **better range**, and **improved performance**.

- **Key Features**:
  - **Maximum Data Rate**: Up to **600 Mbps** (using multiple antennas and channels, known as **MIMO (Multiple Input, Multiple Output)**).
  - **Channel Bonding**: It uses **channel bonding**, which allows combining multiple 20 MHz channels into a single 40 MHz channel to double the available bandwidth.
  - **Modulation**: It uses **OFDM** (like 802.11g), but with improvements and support for multiple antennas.
  - **Dual Band**: It supports both **2.4 GHz** and **5 GHz**, enabling more reliable and faster connections. The **5 GHz** band is less crowded and prone to less interference than 2.4 GHz.
  - **Range**: Significantly better range than 802.11b/g, especially when using the 5 GHz band.

- **Use Cases**:
  - **High-Speed Wi-Fi**: Used in home networks, streaming, gaming, and applications that require faster data transfer.
  - **IoT Devices with High Data Needs**: IoT applications that transmit larger amounts of data, such as video streaming or large file transfers.

---

### **APIs to Configure Wi-Fi Protocol Modes on ESP32**

The **ESP32** allows you to configure which Wi-Fi protocol (802.11b, 802.11g, or 802.11n) to use through its **Wi-Fi APIs**. The ESP32 firmware and SDK (Software Development Kit) expose certain settings and APIs to configure the Wi-Fi mode and the protocol.

#### **Wi-Fi Modes Supported by ESP32**

- **STA Mode** (Station Mode) - Connects to an external Wi-Fi network (such as a router).
- **AP Mode** (Access Point Mode) - Acts as a Wi-Fi access point for other devices to connect to.
- **Station/AP Mode** (Coexistence Mode) - The ESP32 works as both a Station (connecting to a Wi-Fi network) and an AP (creating its own network).
  
### **Configuring Protocol Mode in ESP32**

You can configure the Wi-Fi protocol mode in ESP32 using the **Wi-Fi SDK** (usually `esp_wifi.h` in ESP-IDF). The ESP32 supports various configuration options, which allow you to select the protocol mode:

1. **Set Wi-Fi Mode**:
   - In the ESP32 SDK, you can use the `esp_wifi_set_mode()` function to set the device to either **STA**, **AP**, or **STA/AP** mode.

   Example:
   ```c
   esp_wifi_set_mode(WIFI_MODE_STA);  // Set Wi-Fi to Station (Client) mode
   ```

2. **Set Wi-Fi Channel**:
   - To set the Wi-Fi channel, you can use the `esp_wifi_set_channel()` function.
   
   Example:
   ```c
   esp_wifi_set_channel(6, WIFI_SECOND_CHAN_NONE);  // Set to channel 6
   ```

3. **Set Wi-Fi Protocol (802.11b, 802.11g, 802.11n)**:
   - You can configure the Wi-Fi standard using the `esp_wifi_set_protocol()` function. This is where you specify whether you want to use **802.11b**, **802.11g**, or **802.11n**.

   Example:
   ```c
   esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_11B);  // Set STA mode to use 802.11b
   esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_11G);  // Set STA mode to use 802.11g
   esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_11N);  // Set STA mode to use 802.11n
   ```

4. **Setting the Maximum Data Rate**:
   - You can fine-tune the maximum allowed data rate for the connection. This can be important in scenarios where a specific data rate is required.
   
   Example (Setting maximum data rate for STA mode):
   ```c
   esp_wifi_set_max_tx_power(20);  // Set maximum transmission power to 20dBm (default)
   ```

---

### **Comparison of the Protocols: 802.11b, 802.11g, and 802.11n**

| **Feature**                | **IEEE 802.11b**             | **IEEE 802.11g**             | **IEEE 802.11n**               |
|----------------------------|------------------------------|------------------------------|--------------------------------|
| **Release Year**            | 1999                         | 2003                         | 2009                           |
| **Frequency Band**          | 2.4 GHz                      | 2.4 GHz                      | 2.4 GHz, 5 GHz (dual-band)     |
| **Max Data Rate**           | 11 Mbps                      | 54 Mbps                      | 600 Mbps                       |
| **Modulation**              | DSSS                         | OFDM                         | OFDM + MIMO (Multiple Antennas) |
| **Range**                   | Moderate                     | Better than 802.11b          | Better than 802.11g with dual-band |
| **Compatibility**           | Compatible with older devices| Backward compatible with 802.11b| Backward compatible with 802.11b/g |
| **Use Cases**               | Low-data-rate applications   | Home Wi-Fi networks          | High-speed networks, IoT, streaming |

---

### **Conclusion**

- **IEEE 802.11b**, **IEEE 802.11g**, and **IEEE 802.11n** are all Wi-Fi standards used to define how devices communicate over wireless networks.
- **802.11b** is the slowest but still used in low-data-rate applications, **802.11g** offers faster speeds while remaining compatible with older devices, and **802.11n** is the most advanced of the three, supporting much higher speeds and dual-band operation.
- The **ESP32** allows you to configure which protocol to use based on your needs using simple APIs, enabling flexibility in designing wireless communication for different types of devices and applications.

### Security Protocols


### Advanced Wi-Fi Features


### Power Management


### Custom Protocols


### Throughput


### Wi-Fi Sniffer


### Scanning


### Multiple Antennas


### Channel State Information


### Wi-Fi Aware (NAN)









## Code Explanation 💡

### `main.h`






- ## app_main





## Conclusion 🌟


