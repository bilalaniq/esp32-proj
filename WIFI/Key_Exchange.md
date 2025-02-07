# KEY EXCHANGE

1. **Pre-Shared Key (PSK)**
2. **pairwise master key (PMK)**
3. **4-Way Handshake**                       --`key exchange protocol`
4. **Session Keys**
   - **Pairwise Transient Key (PTK)**
   - **Group Temporal Key (GTK)**
   - **Message Integrity Code (MIC) Key**

5. **Public Key Infrastructure (PKI)**
6. **Simultaneous Authentication of Equals (SAE)**
5. **Extensible Authentication Protocol (EAP)**
6. **EAP-TLS (Transport Layer Security)**
7. **EAP-PEAP (Protected EAP)**
8. **EAP-TTLS (Tunneled Transport Layer Security)**
9. **EAP-FAST (Flexible Authentication via Secure Tunneling)**
10. **EAP-SIM (Subscriber Identity Module)**
11. **EAP-AKA (Authentication and Key Agreement)**



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

---

<br>


- # `4-Way Handshake`

The **4-Way Handshake** is a key part of the **Wi-Fi Protected Access (WPA)** , **WPA2** and **WPA3** protocols used for securing wireless networks. It is responsible for ensuring secure communication between a wireless client (like a smartphone or laptop) and the access point (AP), especially for authenticating and generating encryption keys.

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


### Steps in the 4-Way Handshake (WPA3 if SAE is used)








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

---


### **Why PTK Is Important**

1. **Encrypts Data**: The PTK is the core key used to encrypt all user data between the client and AP.
   
2. **Dynamic Generation**: The PTK is dynamically generated using unique data, making each session secure and distinct. This means that even if an attacker captures the PTK for one session, it cannot be used for others.
   
3. **Prevents Key Reuse**: By generating a new PTK for each session, Wi-Fi networks avoid the risks of key reuse, reducing the chances of successful attacks like brute-force or replay attacks.

---


- ## `Group Temporal Key (GTK)`






- ## `Message Integrity Code (MIC) Key`




