# KEY EXCHANGE

1. **Pre-Shared Key (PSK)**
2. **pairwise master key (PMK)**
3. **4-Way Handshake**                       --`key exchange protocol`
4. **Session Keys**
   - **Pairwise Transient Key (PTK)**
   - **Group Temporal Key (GTK)**
   - **Message Integrity Code (MIC) Key**

5. **Simultaneous Authentication of Equals (SAE)**
6. **Public Key Infrastructure (PKI)**
7. **Extensible Authentication Protocol (EAP)**
8. **EAP-TLS (Transport Layer Security)**
9. **EAP-PEAP (Protected EAP)**
10. **EAP-TTLS (Tunneled Transport Layer Security)**
11. **EAP-FAST (Flexible Authentication via Secure Tunneling)**
12. **EAP-SIM (Subscriber Identity Module)**
13. **EAP-AKA (Authentication and Key Agreement)**



<br>
<br>

- # `Pre-Shared Key (PSK)`

**Pre-Shared Key (PSK)** is a mechanism used for authenticating devices on a Wi-Fi network by sharing a common secret key (password) between the client (e.g., a laptop or smartphone) and the access point (AP, like a Wi-Fi router). PSK is one of the most common and straightforward authentication methods in Wi-Fi networks, particularly for **home networks** or **small businesses**.

---

### **1. Overview of Pre-Shared Key (PSK)**

- **PSK** is a shared secret key (password) that both the client device and the Wi-Fi router (AP) use to encrypt and decrypt the traffic.
- The key is manually configured on both the AP and the client devices.
- PSK is used in **WPA2-Personal** and is also found in **WPA**

---

### **2. How Pre-Shared Key (PSK) Works**

To begin, a **PSK** (Pre-Shared Key) and a **password** are not the same thing.


A **pre-shared key (PSK)** is a super-long series of seemingly random letters and numbers generated when a device joins a network through a Wi-Fi access point (AP). The process begins when a user logs into the network using the SSID (name of the network) and **password** (sometimes called a **passphrase**).

The SSID and password (8-63 characters) are then used to create the **PSK**, which is then used in conjunction with other information to create an even more complex encryption key to protect data sent over the network.

---

### Example:

Here is an example of an SSID, password, and PSK:

- **SSID**: John’s Home Network
- **Password/Passphrase**: `secretpassword123`
- **PSK**: `c9a68e83bfd123d144ec5256bc45682accfb8e8f0561f39f44dd388cba9e86f2`


1. **Key Sharing**:  
   The user or network administrator sets the **PSK** on both the access point (router) and the client devices. This is usually done manually by entering the same passphrase or key on both ends.

2. **Key Derivation**:  
   Once the PSK is set, it is used to derive the actual encryption key, typically via a **hashing algorithm** such as **PBKDF2** (Password-Based Key Derivation Function 2) or **SHA-256**. This derived key is then used for encrypting the data between the client and the AP.

3. **Authentication**:  
   When a client attempts to connect to the Wi-Fi network, it sends a request to the AP. The AP verifies that the client is using the correct PSK by comparing it with the one it has stored. If the keys match, the client is granted access.

4. **Encryption**:  
   After authentication, the derived encryption key is used to encrypt and decrypt data traffic between the AP and the client using an encryption algorithm such as **AES (Advanced Encryption Standard)**.



### **3. Security of PSK**

- **Simple and Fast**:  
  PSK is simple to implement and doesn't require additional infrastructure or a certificate-based system, making it ideal for small-scale deployments (like home networks).
  
- **Weakness**:  
  The biggest vulnerability of PSK is that the shared password is static. If someone learns or cracks the PSK, they can easily gain unauthorized access to the network.
  - If the password is weak, it becomes easier to **brute force** or **dictionary attack** the key.
  - Reusing the same PSK across multiple devices or networks also increases risk.

- **Encryption Strength**:  
  The security of PSK depends heavily on the strength of the passphrase used. A strong, long passphrase makes brute-forcing the key computationally expensive, while a weak passphrase can be cracked more easily.

---

### **4. PSK in WPA2-Personal and WPA3-Personal**

- **WPA2-Personal (Wi-Fi Protected Access 2)**:  
  PSK is the standard authentication method used in WPA2-Personal. The **TKIP** (Temporal Key Integrity Protocol) or **AES** (Advanced Encryption Standard) encryption is used after authentication. WPA2 with PSK is more secure than older protocols (e.g., WEP).

- **WPA3-Personal (Wi-Fi Protected Access 3)**:  
  WPA3 introduces **Simultaneous Authentication of Equals (SAE)**, a more secure form of key exchange than PSK, but PSK can still be used in WPA3-Personal as a fallback for compatibility. SAE provides forward secrecy and stronger protection against offline dictionary attacks.

---

### **6. Benefits of PSK**

- **Ease of Setup**:  
  PSK is quick to configure, as it doesn't require any complex server infrastructure (no RADIUS server, no certificate management).
  
- **No Ongoing Maintenance**:  
  Once the PSK is set on the devices, there's no need for continual management like there would be with certificate-based or server-managed solutions.

- **Compatibility**:  
  PSK is supported across nearly all devices, making it widely compatible, even with older hardware.

---

### **7. Best Practices for Using PSK**

To ensure PSK offers reasonable security, consider the following best practices:

1. **Use a Strong Passphrase**:  
   - The passphrase should be long (at least 16 characters) and complex, including a mix of upper/lowercase letters, numbers, and special characters.
   - Avoid common words, phrases, or patterns that could be easily guessed.
   
2. **Regularly Change the PSK**:  
   Change the PSK periodically (e.g., every 6–12 months) to reduce the risk of compromise.

3. **Avoid Default or Weak Passwords**:  
   Many routers come with default passwords that are easy to guess. Always change the default password to something unique and secure.

4. **Enable WPA2 or WPA3**:  
   Always use WPA2 or WPA3 instead of WEP, as WEP is highly insecure and easily cracked.

5. **Use Unique PSKs for Different Networks**:  
   Don't reuse the same PSK across multiple networks or devices. Each network should have its own unique key.

6. **Monitor Network for Unauthorized Devices**:  
   Periodically check your network for devices you don't recognize and change your PSK if needed.



### Why is a PSK Important?

In essence, the **pre-shared key (PSK)** plays an essential part in the **encryption process** that keeps network traffic secure.

---

<br>

- # `pairwise master key (PMK)`

The **Pairwise Master Key (PMK)** is a key used in **Wi-Fi networks**, specifically in **WPA2** and **WPA3** (Wi-Fi Protected Access 2 and 3), that plays a crucial role in establishing secure communication between a **client device** (such as a laptop, smartphone, or tablet) and a **Wi-Fi access point (AP)**. 

The PMK is not directly provided or shared by the user but is derived from a shared secret (like a **Pre-Shared Key (PSK)** or through **802.1X** authentication in WPA2-Enterprise). It is used as the starting point to generate further encryption keys, including the **PTK (Pairwise Transient Key)**, which is used for encrypting actual data traffic during the session.

---

### **How is PMK Generated?**

The **PMK** can be generated in two different ways depending on the type of Wi-Fi network setup (WPA2-Personal vs. WPA2-Enterprise):

#### **1. In WPA2-Personal (using PSK)**

In WPA2-Personal, the **PMK** is derived from the **Pre-Shared Key (PSK)** (the password or passphrase entered by the user) and other information, primarily the **SSID** (Service Set Identifier) of the network.

Here’s how it works:

1. The **PSK** (user's password) is entered into the device (e.g., smartphone, laptop) and access point (AP).
2. The PSK is combined with the **SSID** (Wi-Fi network name) of the access point using a **cryptographic function** (such as **PBKDF2** – Password-Based Key Derivation Function 2).
3. This process generates the **PMK**, which is a **256-bit key**.
4. The PMK is then used in the **four-way handshake** to generate the **Pairwise Transient Key (PTK)** and other session-specific keys.

#### **2. In WPA2-Enterprise (using 802.1X authentication)**

In WPA2-Enterprise, the **PMK** is derived as a result of the **802.1X authentication process**, which involves the following:

1. The **client device** (supplicant) sends its credentials (such as a username and password, smart card, or certificate) to an **authentication server** (RADIUS server).
2. The **RADIUS server** validates the credentials and generates the **PMK**.
3. The PMK is sent securely back to the access point and client device during the **four-way handshake**.

Unlike WPA2-Personal, which uses a single shared passphrase (PSK), WPA2-Enterprise uses **individualized credentials** and the **RADIUS server** to securely derive the **PMK**.

---

### **PMK’s Role in Key Exchange**

The **PMK** is used in the **four-way handshake** process, where the client and access point exchange cryptographic messages to establish a secure communication channel. The PMK is the foundation upon which further keys are generated:

1. **Four-Way Handshake**:
   - The **four-way handshake** is an essential process in WPA2 and WPA3, which ensures that both the client and access point authenticate each other and derive session keys.
   - The **PMK** is used to derive the **Pairwise Transient Key (PTK)**, which is then used for encrypting the data exchanged between the client and the access point.

2. **Deriving PTK from PMK**:
   - The **PMK** is combined with random values (nonces) generated by the access point and the client (called **Anonce** and **Snonce**), along with the MAC addresses of the devices involved (client and access point).
   - These elements are passed through a cryptographic function (pseudo-random function or PRF) to generate the **PTK**.

---

### **Importance of PMK**

The **PMK** is crucial because it serves as the foundation for generating the keys used to encrypt all communication between the client device and access point. Without the PMK, the **PTK** and, therefore, the **session keys** cannot be generated, and the data traffic between the devices cannot be secured.

Here’s why PMK is important:

1. **Foundation for Encryption**: The PMK is used to derive the **PTK**, which is used for **data encryption**. It ensures that the communication between the devices is encrypted and cannot be intercepted by unauthorized users.
   
2. **Session-Specific**: The PMK is unique to each session. In WPA2-Personal, the PMK is derived from the **PSK** and **SSID**, which are specific to each network. In WPA2-Enterprise, the PMK is derived using **individual credentials** for each device or user.
   
3. **Protects Against Replay Attacks**: Because the PMK is used to generate unique keys for each session, it prevents attackers from replaying traffic captured from previous sessions. Each session has a unique **PMK** and **PTK**, making the keys highly session-specific.
   
4. **Secure Communication**: The PMK ensures that the **pairwise keys** used to encrypt data are derived securely, preventing unauthorized users from accessing or decrypting the data traffic between the client and AP.


### **PMK in the Four-Way Handshake**

The **PMK** is used during the **four-way handshake** to ensure that both the client and the access point can securely exchange data and establish a secure communication channel. Here’s a summary of the steps:

1. **Step 1**: Both the client and access point already know the **PMK** (either derived from PSK or via 802.1X).
2. **Step 2**: The access point sends a nonce (Anonce) to the client.
3. **Step 3**: The client responds with its own nonce (Snonce).
4. **Step 4**: The access point uses the **PMK**, the **Anonce**, the **Snonce**, and the **MAC addresses** of both the client and access point to generate the **PTK**.
5. **Step 5**: The PTK is used to encrypt the actual data traffic exchanged between the client and the access point.

---

### **Summary of PMK’s Role**

- The **PMK** is the **master key** derived from the **PSK** (in WPA2-Personal) or through **802.1X authentication** (in WPA2-Enterprise).
- It is used to securely derive the **PTK**, which is used for **data encryption** during the session.
- The **PMK** is critical for **ensuring secure communications** between the client and access point, as it forms the basis for generating encryption keys.
- In WPA2-Personal, the **PMK** is generated by combining the **PSK** and the **SSID** of the network, while in WPA2-Enterprise, the **PMK** is generated from individual credentials during the **802.1X authentication process**.

**Algorithams**: 
PMK gets generated using SHA-1 in WPA2.
PMK gets generated using ECDH in WPA3/OWE


Also note that, Insider Attacks are still possible with WPA2, and even with WPA2-PMF (802.11w) who knows the SSID , Password and captured 4-way handshake EAPOL Frames, because all the clients will have same PMK in WPA2 and WPA2-PMF.

But with WPA3 PMF , Insider Attacks are not possible because, we can’t get the PMK without the private keys. And the each client will have separate PMK.



---

<br>


- # `4-Way Handshake`

The **4-Way Handshake** is a key part of the **Wi-Fi Protected Access (WPA)** and **WPA2** protocols used for securing wireless networks. It is responsible for ensuring secure communication between a wireless client (like a smartphone or laptop) and the access point (AP), especially for authenticating and generating encryption keys.

Here’s a breakdown of the 4-Way Handshake process in detail:

### Overview
The 4-Way Handshake consists of four messages exchanged between the **client** (the station) and the **access point (AP)**, which is necessary for:
1. **Authentication**: Verifying that both the AP and client know the correct credentials.
2. **Key Exchange**: Generating a shared encryption key to secure the communication between the client and the AP.
3. **Session Key Generation**: The 4-Way Handshake is responsible for the creation of session keys used to encrypt data after the handshake is complete.

### Steps in the 4-Way Handshake (WPA & WPA2 , work same for WPA3 if PSK is used)

#### 1. **Message 1: AP to Client (Nonce and SNonce)**
   - The **access point (AP)** sends a message (Message 1) to the **client**. This message includes:
     - **ANonce**: A random number generated by the AP, which will be used to help create a unique session key.
     - **WPA2 Protocol Version**: This identifies the version of WPA being used (WPA or WPA2).
     - The message also includes a **Pairwise Cipher Suite** and a **Group Cipher Suite** (for multicast communication).
     - The AP does not yet send any data to decrypt in this step, it’s just sending an initial nonce to start the process.

   **Message 1 Breakdown**:
   - AP generates a random nonce called **ANonce**.
   - The AP also contains a MAC address in this message for identification.
   - This message doesn’t use encryption because the client has not yet been authenticated.

#### 2. **Message 2: Client to AP (SNonce and MIC)**
   - The **client** responds with **Message 2**, which includes:
     - **SNonce**: Another random number generated by the client, which, along with the AP's nonce, will contribute to creating the encryption keys.
     - **Message Integrity Code (MIC)**: This is a hashed value (generated using the passphrase or PSK) to prove that the client has the correct key.
     - The **client** also confirms that it is ready to begin secure communication by including other data like the supported encryption algorithms.

   **Message 2 Breakdown**:
   - Client generates its own **SNonce** and sends it to the AP.
   - The client calculates a **MIC** based on the pre-shared key (PSK) or credentials, which ensures that the AP can validate the authenticity of the client.
   - The MIC ensures integrity and protects against replay attacks or tampering.

#### 3. **Message 3: AP to Client (Confirm and Key Derivation)**
   - The **AP** now responds to the client with **Message 3**, which contains:
     - **GTK (Group Temporal Key)**: A key for encrypting multicast and broadcast frames (important for securing group communication).
     - The **MIC**: A verification code to ensure that the message hasn’t been tampered with.
     - The **AP** also confirms the security settings and completes the negotiation process for unicast encryption keys.

   **Message 3 Breakdown**:
   - The AP confirms that it has successfully received the client’s **SNonce** and will now send the **Group Temporal Key (GTK)** to the client.
   - The **MIC** is used to verify that the message is coming from the AP and hasn’t been altered.

#### 4. **Message 4: Client to AP (Key Confirmation)**
   - The **client** sends a final confirmation message (**Message 4**) to the AP, indicating that the keys have been established successfully.
   - This message includes:
     - A **MIC** to verify the integrity of the message.
     - Confirmation that the client has received the GTK and is now ready to securely communicate with the AP.

   **Message 4 Breakdown**:
   - The client responds to the AP, acknowledging the successful key exchange and confirming that all of the keys are set up.
   - The **MIC** ensures that this confirmation is authentic.

### Final Key Derivation
After the 4-Way Handshake is completed:
- Both the AP and client now have the same **Pairwise Transient Key (PTK)**, a unique session key derived from the **ANonce**, **SNonce**, and the shared password or pre-shared key (PSK).
- The **PTK** is used to encrypt unicast (client-to-AP and AP-to-client) communications.
- The **GTK** (Group Temporal Key) is used for multicast and broadcast encryption, ensuring that data sent to multiple clients is also secured.

### Key Security Concepts
- **ANonce & SNonce**: These nonces ensure that each session has a unique key, preventing replay attacks.
- **MIC (Message Integrity Code)**: This is a cryptographic hash that ensures the integrity of the messages. It is part of the security mechanism that ensures the handshake hasn’t been tampered with.
- **Pairwise Transient Key (PTK)**: This is the main key used for encrypting the communication between the client and AP. It’s derived from the ANonce, SNonce, and PSK.

### Why It’s Important
- **Authentication**: Ensures that both the client and AP are legitimate and using the correct credentials.
- **Key Generation**: The 4-Way Handshake generates fresh keys for each session, ensuring that even if one key is compromised, the next session will have a different key.
- **Protection Against Replay Attacks**: The use of nonces and the MIC ensures that attackers can’t reuse old messages to fool the system into granting access.

In summary, the 4-Way Handshake is crucial for establishing a secure Wi-Fi connection, ensuring that encryption keys are shared securely, and that both the access point and client are authenticated. It creates a fresh set of keys for each session, reducing the likelihood of security breaches.




No, WPA3 does not use the traditional "4-way handshake" as seen in older protocols like WPA2; instead, it utilizes a different handshake mechanism called "Simultaneous Authentication of Equals (SAE)" which is based on the Dragonfly handshake, offering improved security against brute-force attacks on passwords. 



overall the 4 way handshake looks like this

![wifi_sec](https://praneethwifi.in/wp-content/uploads/2020/03/image-26.png)


---

<br>
<br>



- # `Session Keys`

A **session key** is a temporary encryption key used to secure the communication between two parties (e.g., a client and an access point) during a specific communication session. The session key is valid only for the duration of that session and is discarded afterward. This key is used to encrypt and decrypt data exchanged between the parties to ensure confidentiality, integrity, and security during the session.

### Key Characteristics of Session Keys:

1. **Temporary**: Session keys are only valid for the duration of a specific session. Once the session ends (e.g., the client disconnects or the session times out), the session key is discarded.

2. **Unique**: Each session has its own unique set of session keys. This ensures that even if one session is compromised, the attacker cannot decrypt past or future sessions.

3. **Derived during the handshake**: Session keys are typically generated during a handshake process (e.g., the **4-Way Handshake** in WPA2 or the **SAE Handshake** in WPA3). These keys are derived based on factors like:
   - The shared secret (e.g., a password or PSK).
   - Nonces (random numbers generated during the handshake).
   - The MAC addresses of the client and the access point.

4. **Purpose**: The main purpose of session keys is to **encrypt** the data exchanged between the two parties and to ensure **data integrity** (making sure the data has not been tampered with).


### How Session Keys Work in WPA2/WPA3:

1. **Session Key Generation**:
   - During the **handshake** process (e.g., **4-Way Handshake** for WPA2), the client and access point exchange certain values like **nonces** (random numbers) and use the **Pre-Shared Key (PSK)** (WPA2) or **Simultaneous Authentication of Equals (SAE)** (WPA3) to generate the **session keys**.
   
2. **Encryption**:
   - Once the session keys are derived, they are used to encrypt the actual data sent between the client and the access point. This ensures that even if the data is intercepted, it cannot be read by unauthorized parties.

3. **Session Key Expiry**:
   - Once the communication session ends (e.g., when the client disconnects), the session keys are no longer valid, and new session keys will be generated for future sessions.

In summary, a **session key** is a temporary encryption key used for securing communication between two parties in a specific session, ensuring that data is protected from eavesdropping and tampering.



These are the primary session keys used for encryption and integrity in WPA2 and WPA3. The ANonce and SNonce are nonces used during the handshake and are not considered session keys themselves but are crucial in the key derivation process.


1. **Pairwise Transient Key (PTK)**
2. **Group Temporal Key (GTK)**
3. **Message Integrity Code (MIC) Key**


<br>
<br>

- ## `pairwise transit key (PTK)`

The **Pairwise Transient Key (PTK)** is a key used in **Wi-Fi networks**, specifically in **WPA2** and **WPA3**, for **encrypting the communication** between a **client device (supplicant)** and the **Wi-Fi access point (AP, or authenticator)**. PTK is derived during the **four-way handshake** and ensures that data exchanged between the client and AP is kept secure.

In simple terms, PTK is a session-specific encryption key that protects the confidentiality and integrity of data being transmitted over the Wi-Fi network.

---

### **How is PTK Generated?**

The PTK is not a fixed, pre-shared key like the **PSK**. Instead, it is dynamically generated for each session after the initial authentication. The generation process involves a series of steps during the **four-way handshake** and uses several pieces of information exchanged between the client and the access point.

The PTK generation process is as follows:

1. **PSK (Pre-Shared Key) & PMK (Pairwise Master Key)**
   - The **Pre-Shared Key (PSK)** is the password or passphrase used by the client and access point to authenticate each other.
   - During the authentication process (in WPA2 or WPA3), the **PSK** is used to derive the **PMK** (Pairwise Master Key).
   - **PMK** is the starting point for the PTK generation. If **802.1X** authentication is used (WPA2-Enterprise), the **PMK** is derived from the credentials provided by the client and verified by the **RADIUS server**.

2. **Four-Way Handshake**
   - The **four-way handshake** is a key exchange process in WPA2/WPA3 used to securely establish encryption keys between the client and access point after the authentication phase.
   - The **four-way handshake** involves the following exchanges:
     - **Message 1**: The AP sends a nonce (**Anonce**) to the client.
     - **Message 2**: The client sends its nonce (**Snonce**) to the AP.
     - **Message 3**: The AP sends a message to confirm that the client can now begin encryption.
     - **Message 4**: The client acknowledges the final step and begins encrypting communication.

3. **Information Used in PTK Generation**
   To generate the PTK, the following five pieces of information are used:
   
   - **PMK**: The Pairwise Master Key, which comes from the PSK or, in the case of WPA2-Enterprise, from 802.1X authentication.
   - **Anonce**: A **random number** generated by the access point (Authenticator Nonce).
   - **Snonce**: A **random number** generated by the client device (Supplicant Nonce).
   - **MAC AA**: The MAC address of the access point (Authenticator).
   - **MAC SA**: The MAC address of the client device (Supplicant).

   These five elements are combined in a cryptographic function known as the **Pseudo-Random Function (PRF)**, which produces the **PTK**.

4. **The PTK Generation Formula**

   The PTK is generated using the following formula:

   ```
   PTK = PRF(PMK + Anonce + Snonce + MAC(AA) + MAC(SA))
   ```

   Here:
   - **PRF** refers to a **Pseudo-Random Function**, which is a cryptographic function designed to produce random output.
   - The **PTK** is derived from combining the PMK, Anonce, Snonce, and the MAC addresses of the AP and client device.
   - The output is a **256-bit key** (32 bytes) that is used for encryption during the session.

---

### **What Does PTK Do?**

Once the PTK is generated, it is used to protect the communication between the client device and the access point. The PTK helps with the following functions:

1. **Encryption**:
   - The **PTK** is used to **encrypt** the data transmitted between the client and the access point. It ensures that the communication is confidential and cannot be easily intercepted or read by third parties.
   
2. **Integrity Protection**:
   - The PTK is used to ensure the **integrity** of the data. It guarantees that data has not been tampered with during transmission. If any data is modified during transit, the PTK-based integrity checks will detect it.
   
3. **Session Uniqueness**:
   - The PTK is **unique** for each session, meaning that each time a device connects to a network, the PTK is re-generated through the handshake process. This prevents replay attacks and ensures that each session is encrypted independently from previous or future sessions.

---

### **Components of PTK**

The PTK is not a single, simple key but a collection of different keys derived from the **PMK**:

1. **KCK (Key Confirmation Key)**:  
   - Used for **message integrity**. It is used to protect the integrity of handshake messages.
   
2. **KEK (Key Encryption Key)**:  
   - Used to encrypt the **pairwise keys** that are sent during the handshake. KEK ensures that the encryption keys are securely shared.
   
3. **TK (Temporal Key)**:  
   - Used to **encrypt user data** during the session. The TK is the key that actually encrypts the traffic between the client and AP.
   
4. **MIC (Message Integrity Code)**:  
   - Used for **message authentication** to detect any tampering with the messages.



Below are the contents of the PTK and length of the different Keys in the PTK.

PTK for the WPA3 Handshake

```bash
e4cecf6a384a15975a919295b18716ba8754791e2129dc11bca0b9f03d4d2e2ca1ae967dacdd65a145d5d95f3c6322fc702e6a4bff7f000000dc6a3541ad8883
```

<br>

![ptk](https://praneethwifi.in/wp-content/uploads/2020/01/image-70.png)

<br>
<br>


---


### **Why PTK Is Important**

1. **Encrypts Data**: The PTK is the core key used to encrypt all user data between the client and AP.
   
2. **Dynamic Generation**: The PTK is dynamically generated using unique data, making each session secure and distinct. This means that even if an attacker captures the PTK for one session, it cannot be used for others.
   
3. **Prevents Key Reuse**: By generating a new PTK for each session, Wi-Fi networks avoid the risks of key reuse, reducing the chances of successful attacks like brute-force or replay attacks.



Algoritham:
PTK gets generated using SHA-1 in WPA2.
PTK gets generated using SHA-256 in WPA2-PMF/WPA3/OWE.



How easy is it Know the PTK ?

It will be easy to get the PTK when we are using WPA2. It will be difficult to get the PTK when we are using WPA3 . If we get the PTK then we can verify the MIC for the 4-way Handshake for WPA3.
Note that , Getting the PMK is not an easy task in WPA3 even if we have the SSID, Password, and captured 4-way Handshake. Because we will not have the private keys that were used to generate the PMK.






---


- ## `Group Temporal Key (GTK)`

The **Group Temporal Key (GTK)** is a **symmetric encryption key** used in **Wi-Fi networks** (WPA2/WPA3) to secure **multicast** and **broadcast** traffic between the access point (AP) and multiple clients (devices) on the network. It is one of the important session keys in WPA2 and WPA3 security protocols.

Here's an in-depth breakdown of the **GTK**:

---

### **1. Purpose of GTK:**
The GTK is specifically designed for encrypting **group communication**, meaning the traffic that is intended to be received by **multiple clients** at the same time, such as broadcast and multicast messages. These are messages that the AP sends to **all devices** in the network.

#### Example of Group Traffic:
- **Multicast Traffic**: Sent from the AP to a group of clients, like a video stream.
- **Broadcast Traffic**: Sent from the AP to all clients, such as DHCP requests or other network-wide communications.

The **GTK** is **shared by all clients** connected to the AP and is used to encrypt and decrypt group messages.

---

### **2. GTK vs. PTK:**

- **Pairwise Transient Key (PTK)**: This key is used to secure **unicast** communication between a specific client and the AP (one-to-one communication).
- **GTK**: This key is used to secure **multicast** and **broadcast** communication, i.e., one-to-many communication (sent to multiple clients).

### **3. How GTK is Generated:**
The **GTK** is generated during the **4-Way Handshake** (in WPA2) or **SAE Handshake** (in WPA3), but unlike the **PTK**, the GTK is shared by all clients connected to the AP. Here’s how it works:

1. **During the Handshake**:
   - **WPA2 (4-Way Handshake)**: After the pairwise session keys (PTK) are established, the AP sends the **GTK** to the client using the **Key Message 3** of the 4-Way Handshake.
   - **WPA3 (SAE Handshake)**: The AP also sends the **GTK** during the SAE handshake process.

2. **Transmission to Clients**:
   - The **AP encrypts** the GTK using the **PTK** (the client-specific key derived in the 4-Way Handshake) and sends it in the handshake message.
   - The **client decrypts** the GTK using the PTK, and the same GTK is used for all clients connected to the AP.

---

### **4. Security of GTK:**
The **GTK** is designed to be kept secure from unauthorized access. If an attacker gains access to the GTK, they could decrypt multicast/broadcast traffic. Therefore:

- **GTK is sent in an encrypted format**: The AP encrypts the GTK with the PTK (which is unique to each client). This ensures that even if an attacker captures the message, they cannot decrypt the GTK without the PTK.
- **Re-keying**: The AP periodically re-generates and distributes a new GTK to the clients to enhance security and reduce the risk of a key being compromised over time. This is done through a process known as **GTK rekeying**.

---

### **5. Usage of GTK:**
Once the GTK is shared and securely delivered to the client:

- The **client** uses the **GTK** to decrypt incoming **multicast** and **broadcast** traffic.
- Similarly, the **AP** uses the **GTK** to encrypt multicast and broadcast traffic it sends to clients.

This key ensures that all clients in the network can securely receive common group messages without requiring individual keys for each device.

---

### **6. GTK and Key Hierarchy:**
- The **GTK** is derived from the **Pairwise Master Key (PMK)** during the handshake process, but unlike the PTK (which is derived uniquely for each client), the GTK is the same for all clients connected to the AP.
- The **AP** is responsible for managing the GTK, including distributing it securely to clients and periodically changing it to maintain security.
- **Key Rotation**: Periodic changes to the GTK help mitigate risks associated with long-term key usage. This rotation is an important part of network security, ensuring that even if a GTK is exposed, it won’t be useful indefinitely.

---

### **7. How GTK Works in WPA2/WPA3:**

- **WPA2**:
  - The **4-Way Handshake** involves the exchange of nonces, message integrity codes (MIC), and keys like the **PTK**. Once the PTK is established, the **AP** sends the **GTK** to the client in the third message of the handshake, encrypted with the PTK.
  
- **WPA3**:
  - In WPA3, the process is similar, but the authentication method (SAE) is more secure, using Diffie-Hellman for key exchange. The GTK is still encrypted using the **PTK**, and the **AP** sends it to clients during the handshake process.



### **9. Summary of GTK Key Points:**

- **Purpose**: Secures **multicast** and **broadcast** traffic.
- **Generated** during the **4-Way Handshake (WPA2)** or **SAE Handshake (WPA3)**.
- **Encrypted** with the **PTK** to ensure only authorized clients can access it.
- **Shared among all clients** connected to the AP.
- **Periodically re-keyed** to enhance security.
- **Critical for securing group communication** in WPA2 and WPA3 networks.

---

The **GTK** is a vital element of WPA2 and WPA3's overall security architecture, ensuring that multicast and broadcast communications within the network are kept secure.



- ## `Message Integrity Code (MIC) Key`

**Message Integrity Code (MIC)** plays a critical role in ensuring the integrity and authenticity of data transmitted over wireless networks, particularly in the context of **WPA2 (Wi-Fi Protected Access 2)** and **WPA3** security protocols. It is a part of the **Integrity Check** mechanism used to safeguard data from tampering, ensuring that the transmitted message has not been altered by unauthorized parties.

Here’s a detailed look at how MIC is used in Wi-Fi security:

### 1. **Role of MIC in Wi-Fi (WPA2/WPA3)**
In the context of Wi-Fi security, **MIC** is primarily used to protect data packets from being modified during transmission. This helps ensure that the integrity of the message is maintained and that the data has not been tampered with. MIC is used to:

- **Verify Message Integrity:** MIC helps ensure that the message content has not been altered during transmission.
- **Prevent Replay Attacks:** It makes it difficult for attackers to replay old or intercepted messages.
- **Authenticate Messages:** It provides a way to verify that the message came from an authorized sender and hasn't been forged.

### 2. **How MIC Works in WPA2/WPA3**
Wi-Fi networks typically use **WPA2** (or the newer **WPA3**) for securing wireless communications. Both protocols make use of a MIC in the **Message Integrity Check (MIC)** field to verify the authenticity of each transmitted packet.




Here's how it works in the Wi-Fi context:

#### a. **WPA2 (and WPA3) Encryption and MIC**
In WPA2 and WPA3, the **MIC** is used alongside **AES encryption** in the **Counter Mode with Cipher Block Chaining Message Authentication Code (CCM)** mode. 

What is AES Encryption?
AES (Advanced Encryption Standard) is a strong encryption algorithm used to scramble data so that it cannot be read by anyone who doesn’t have the correct key. In WPA2/WPA3, AES is used to encrypt the data being sent over the Wi-Fi network.

What is CCM Mode?
CCM stands for Counter Mode with Cipher Block Chaining Message Authentication Code. It’s a mode of operation that combines two things:

1. Encryption: Using AES in Counter Mode (CTR) to encrypt the data.

2.  Integrity Protection: Using a Message Authentication Code (MAC) to ensure the data hasn’t been tampered with.

if you want to learn about CCM [CLICK HERE](./CCM.md)


AES Encryption: The data is encrypted using AES in Counter Mode (CTR). This ensures confidentiality—no one can read the data without the correct key.

MIC (Message Integrity Code): A MIC is calculated for the message using the CCM mode. This MIC is like a fingerprint of the message. If even a single bit of the message is changed, the MIC will not match, and the receiver will know the message has been tampered with.


1. **Data Encryption and MIC Calculation:** 
   - When a device (like a router or client) sends data over the network, it first encrypts the data using **AES encryption**.
   - After encrypting the data, it computes the **MIC** for the packet, which is essentially a hash of the message combined with a secret key (known only to the devices in the Wi-Fi network).
   
2. **MIC in the Packet:**
   - The MIC value is then appended to the message. This combination of the encrypted message and the MIC is what gets sent over the air.
   
3. **Verification by the Receiver:**
   - When the receiver (e.g., another device in the Wi-Fi network) gets the packet, it uses the **same secret key** and **algorithm** (e.g., HMAC-SHA1 or a similar function) to recompute the MIC from the received message.
   - If the recomputed MIC matches the one that was sent, the message is verified as intact (i.e., not tampered with).
   - If the MICs don't match, it indicates that the message has been modified or corrupted, and the receiver can discard the packet and request a retransmission.

#### b. **MIC in WPA2-PSK (Pre-shared Key) Mode**
In **WPA2-PSK** (Pre-shared Key) mode, the MIC also plays a role in **ensuring the integrity of the handshake process** when establishing a secure communication channel between the client and the access point.

During the **4-way handshake** (which is part of the process of establishing a secure connection between a client and an access point), the MIC ensures that the handshake messages are authentic and haven't been tampered with by a man-in-the-middle (MITM) attacker.

The process is as follows:
1. The client and access point exchange authentication messages during the 4-way handshake.
2. Each of these messages is protected with a MIC to prevent them from being altered.
3. The MIC prevents attackers from manipulating the messages, ensuring that only the devices with the correct pre-shared key can successfully complete the handshake.

### 3. **MIC in WPA3 (Enhanced Security)**
**WPA3** builds upon WPA2 and introduces stronger encryption and integrity mechanisms, but the concept of MIC remains central. WPA3 introduces **Simultaneous Authentication of Equals (SAE)**, a more secure way of establishing a key for encryption during the handshake process.

- **In WPA3:** The MIC still ensures the integrity of the communication, but with additional protections, especially in environments where attackers may try to guess the shared keys or intercept the initial handshake messages. The use of **SAE** reduces the risk of offline attacks and makes the MIC integrity check more resistant to tampering.

### 4. **Security Benefits of MIC in Wi-Fi**
- **Tamper Detection:** MIC allows devices to detect if the data packets have been altered. This is crucial for ensuring that the messages sent over the air remain secure and haven't been tampered with by attackers.
- **Replay Attack Prevention:** By using a combination of the message, encryption, and MIC, WPA2/WPA3 can prevent attackers from replaying previously captured packets. Even if the packet is intercepted, it can't be reused without the correct MIC and encryption keys.
- **Authentication:** The MIC mechanism ensures that the device sending the message is the legitimate one, as the MIC is based on a shared secret key.

### 5. **What Happens if the MIC Doesn't Match?**
If the MIC value in a received message doesn't match the calculated MIC, it implies that the message has either been altered or corrupted during transmission. When this happens:
- The receiving device will typically discard the corrupted message.
- It may also request a retransmission of the message.
- The event may be logged, and the device might take further security measures (such as raising an alert or initiating a security protocol to block potential attackers).

### 6. **Challenges and Limitations**
- **Key Management:** The security of MIC is heavily reliant on the secure management of the keys used to generate and verify the MIC. If an attacker gains access to the key, they can generate valid MICs for malicious messages.
- **Replay Attacks in WPA2-PSK:** Without additional protection (such as timestamps or nonces), WPA2 in certain configurations could still be vulnerable to replay attacks. WPA3 improves upon this by introducing additional protections.



**Algorithams**:
MIC gets generated using SHA-1 in WPA2.
MIC gets generated using AES-CMAC in WPA2-PMF/WPA3/WPA2-PMF.

<br>
<br>


Observe the below figure to check the differences between the security mechanisms. Check what algorithms are used to generate PMK, PTK, and MIC in different wireless security mechanisms.
![wireless security mechanisms](https://praneethwifi.in/wp-content/uploads/2020/03/security.jpg)

<br>
<br>
<br>


- # `Simultaneous Authentication of Equals (SAE)`
**Simultaneous Authentication of Equals (SAE)** is a key feature of WPA3 (Wi-Fi Protected Access 3) that improves security in wireless networks, specifically in the process of password-based authentication. It replaces the Pre-Shared Key (PSK) authentication method used in WPA2 with a more secure mechanism. Here's a detailed explanation of SAE and how it works in WPA3:

### What is SAE?

SAE is a password-authenticated key exchange (PAKE) protocol that provides a secure method for two parties (the client and the access point) to authenticate each other using a shared password (e.g., the Wi-Fi password) without the risk of exposing the password to eavesdroppers. It is designed to prevent offline dictionary attacks, which are a serious vulnerability in WPA2's PSK method. SAE is a form of **Simultaneous Authentication**, meaning both parties (the client and the access point) authenticate each other in a way that does not involve sending the password directly.

### Key Features of SAE:
- **Mutual Authentication**: Both the client and the access point authenticate each other during the process.
- **Resistance to Dictionary Attacks**: SAE is designed to thwart offline dictionary attacks by ensuring that the password is not directly exposed during the exchange.
- **Forward Secrecy**: SAE ensures that if a session key is compromised in the future, it does not expose past communications.
- **Cryptographic Strength**: SAE uses strong cryptographic techniques to secure the authentication process.

### How SAE Works in WPA3

SAE operates using a variation of the **Dragonfly Key Exchange** (a form of elliptic curve Diffie-Hellman, or ECDH), which allows for secure key exchange without directly revealing the password. Here's a step-by-step breakdown of the process:

#### 1. **Initial Setup**:
   - Both the client (station) and the access point (AP) have the same password (shared secret).
   - The password is not directly transmitted or used to generate a key. Instead, the parties perform an authentication protocol to derive a shared session key.

#### 2. **Commitment Phase**:
   - The client generates a random number (let's call it **X**) and sends it to the access point along with a cryptographic commitment based on the password.
   - The access point also generates a random number (**Y**) and sends it to the client along with its cryptographic commitment.
   - These commitments are based on the password, but crucially, they do not reveal the password itself.
   - The client and AP each calculate a **value (z)** based on their own random number and the commitment sent by the other party.

#### 3. **Exchange Phase**:
   - Both the client and the AP now use their respective random numbers and commitments to derive a shared secret (a key material) that is used for the encryption of future communications.
   - During this phase, both the client and the AP prove that they know the password without revealing it.

#### 4. **Verification Phase**:
   - Once both sides have computed the shared session key, they verify each other's knowledge of the password by performing a **hash** of the shared key.
   - The verification ensures that both parties are authenticated, i.e., that both know the password and have correctly derived the same shared secret.
   - If either the client or the AP fails to compute the correct key, authentication fails and the connection is not established.

#### 5. **Session Key Derivation**:
   - After successful mutual authentication, the shared session key is derived from the exchanged values and used for encrypting the traffic between the client and the AP.


### Cryptographic Underpinnings of SAE

SAE uses elliptic curve cryptography (ECC) and a variation of the **Dragonfly Key Exchange** protocol, which is based on Diffie-Hellman key exchange. The key elements of the cryptographic process include:

- **Elliptic Curve Diffie-Hellman (ECDH)**: This is a form of public-key cryptography used to derive the shared secret. Both parties generate their own private/public key pairs and exchange public keys. The shared secret is then derived using the other party's public key and the party’s own private key.
- **Commitments and Hashing**: The cryptographic commitments are used to ensure that both the client and AP have the same password and that they can derive the same shared secret without directly transmitting the password. This makes SAE resistant to man-in-the-middle attacks.
- **Hashing Functions**: SHA-256 (part of the SHA-2 family) is often used for hashing during the process to ensure the integrity and security of the exchanged data.


In WPA2-PSK we do have a common PMK that is being generated. This PMK is same for all the clients, and it is also easy to get this PMK through the 4-way handshake with the sniffer captures with known SSID and passphrase.

What is new in the WPA3?

Our final goal here is to generate the PMK.

WPA3 will replace the PSK with SAE( Simultaneous Authentication of Equals (SAE) ). In WPA3 each client will have a different PMK that is being generated using the dragonfly frame exchange. It is not possible to get the PMK even if we capture the 4-way handshake. 

SAE is based on  Elliptic Curve Diffie–Hellman key exchange. Advantage of using the  Diffie–Hellman is that both the parties will generate the public/private key pair,.  Diffie–Hellman key exchange establishes a shared secret between two parties that can be used for secret communication for exchanging data. Below diagram shows the DH algorithm concept.


---

![DH](https://praneethwifi.in/wp-content/uploads/2024/02/screenshot-2024-02-06-at-9.46.13-am.png)

<br>
<br>

In the above figure both parties generate public and private keys and public keys are exchanged, but not their private keys. And both of them agree upon the common shared sceret.
WPA3 is also uses the similar method , but it uses Elliptic curve cryptography Diffie Helmen key exchange, and it is not an easy task to find out the  shared secret that is being generated without the private keys. And every time there will be new private keys gets generated, so perfect forward secrecy is given.

An elliptic curve is the set of points that satisfy a specific mathematical equation. Elliptic curve looks like the below picture.

![elliptic curve](https://cdn.arstechnica.net/wp-content/uploads/2013/10/elliptic-curve-crypt-image00.png)

The below equation satisfies the Elliptic curve.

```bash
Y^2=x^3+a.x+b (modulo p)
```

if you want to learn about Dragonfly Key Exchange [click here](./Dragonfly_Key_Exchange.md)


---


<br>
<br>



- # `Public Key Infrastructure (PKI)`



- # `Extensible Authentication Protocol (EAP)`

- # `EAP-TLS (Transport Layer Security)`


- # `EAP-PEAP (Protected EAP)`


- # `EAP-TTLS (Tunneled Transport Layer Security)`


- # `EAP-FAST (Flexible Authentication via Secure Tunneling)`


- # `EAP-SIM (Subscriber Identity Module)`

- # `EAP-AKA (Authentication and Key Agreement)`




