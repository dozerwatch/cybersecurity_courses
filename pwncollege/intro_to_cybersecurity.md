# Introduction to Cybersecurity
- [Talking Web](#talking-web)
- [Building A Web Server](#building-a-web-server)
    - [Linux Processes](#linux-processes)
    - [Network System Calls](#network-system-calls)
- [Intercepting Communication](#intercepting-communication)
    - [Ethernet](#ethernet)
    - [Internet](#internet)
    - [Transmission Control Protocol](#transmission-control-protocol)
    - [ARP](#address-resolution-protocol)
    - [CIDR](#cidr-notation-classless-inter-domain-routing)
- [Cryptography](#cryptography)
    - [One-time-pad](#one-time-pad)
    - [Encryption Properties](#encyption-properties)
    - [AES](#advanced-encryption-standard-aes)
    - [Diffie-Hellman Key Exchange](#diffie-hellman-key-exchange)
    - [Asymmetric Encryption](#asymmetric-encryption)
    - [RSA](#rivest-shamir-adleman-rsa)
    - [RSA Key Generation](#rsa-key-generation)
    - [Hashing](#hashing)
    - [Trust](#trust)
- [Web Security](#web-security)
    - [Injection](#injection)
    - [Same-Origin Policy](#same-origin-policy)





## Talking Web
The *World Wide Web* is a web of information connected to other information via hypertexts. 

The *WWW* works because all systems speak the standardized language, HTTP.

The *Internet* is the backbone of the *WWW*. It provides a way to transmit data from one system to another. 

The *TCP/IP Protocol* defines how all systems must transmit data. *HTTP* is standardized through RFCs. The first one is RFC 1945.

```html
Request-Line = Method        Request-URI  HTTP-Version  CRLF
Status-Line  = HTTP-Version  Status-Code  Reason-Phrase CRLF

HTTP URL Scheme
<scheme>://<host>:<port>/<path>?<query>#<fragment>

Content-Type: application/x-www-form-urlencoded - name=Hong
Content-Type: application/json                  - {"name": "Hong"}
```

HTTP is a stateless protocol, but can be made stateful using HTTP Headers, namely cookies.

Session ID help combat the security concerns of using raw state in cookies.







## Building A Web Server

### Linux Processes
We are **not** allowed to manipulate hardware directly, instead we have to talk to the **OS** using `syscalls`.

The **kernal** keeps track of the state of processes. Processes are just **blobs of data** living in kernal memory, which is located at the bottom of memory (high address).

`syscalls` just manipulate this kernal memory. 

The **kernal**, in some sense, is a library of code. A `syscall` basically redirects control flow into kernal controlled code.

`struct task_struct` is the blob is data managing the state of a process in kernal memory.

`struct task_struct *current` is a global variable that keeps track of the current executing process.

### Network System Calls

- `socket` is the network version of a file. It is also a type of file! It creates an endpoint for communication.
- An address follows the structure:
    ```C
    struct sockaddr_in {
        uint16_t sa_family;
        uint8_t sa_data[14];
    };
    ```
    - `uint16_t` represents 2 bytes
    - `uint8_t` represents 1 byte

- The address structure for **Internet** is:
    ```C
    struct sockaddr_in {
        uint16_t sin_family;
        uint16_t sin_port;
        uint32_t sin_addr;
        uint8_t __pad[8];
    };
    ```
    - `AF_INET` has value `2` and is a part of `sin_family`.
    - `htons`, host to network, converts little-endian to big-endian.
    - `0.0.0.0` binds to any network interface.

Networking likes to work in **big-endian**.
- `bind` assigns an address to a socket.
- `listen` listens for incoming connection requests and puts them into a backlog queue.
- `accept` extracts first connection request on queue and creates a new connected socket, returning a new FD for it.







## Intercepting Communication
![dynamic network](/pwncollege/images/dynamic_network.png)

**In order to attack a system, we must understand the system.**

There are three different ways to intercept communication:
1. At the source
2. Middle-man
3. At the destination

### Ethernet
- physically connected
- Hosts are directly linked to each other.
- **(Host A --> Host B)**: A: eth0 --> vethA --> bridge0 --> vethB --> B: eth0
- Ethernet Packet Structure:
    ```
    6 bytes - Destinaction MAC addres
    6 bytes - Source MAC address
    2 bytes - Type
    ```
### Internet
- routing, hosts are not physically linked
- Type: `0x08` `0x00` - Internet protocol
- The Internet packet structure is more complex
    ```
    4 bits  - Version
    4 bits  - Internet Header Length
    1 byte  - Differentiated Services Field
    2 bytes - Total Length
    2 bytes - Identification
    3 bits  - Flags
    13 bits - Fragment Offset
    1 byte  - Time To Live
    1 byte  - Protocol
    2 bytes - Header Checksum
    4 bytes - Source IP Address
    4 bytes - Destination IP Address
    ? bytes - Options
    ```
### Transmission Control Protocol
- Protocol: `0x06` - TCP
- Enables a stateful interaction
- Introduces order, reliability, and ports
- Packet structure
    ```
    2 bytes - Source port
    2 bytes - Destination port
    4 bytes - Sequence number: Start with randomly initalized value, maps amount of data sent
    4 bytes - Acknowledgement number: Start with randomly initialized value, maps amount of data recieved
    1 octet - Data Offset: Determines number of bytes used for header and the rest is data
    3 bits  - Reserved
    9 bits - Flags
    2 bytes - Window Size: Data max size
    2 bytes - Checksum: of the header
    2 bytes - Urgent Pointer: Indicate how part of data is urgent
    ? bytes - Options
    ```
- Sequence and Acknowledgement number relates to state
- Flags:
    - URG: indicate Urgent Pointer field is significant
    - ACK: acknowledge other's seq number
    - PSH: push forward the data immediately
    - RST: reset the connection
    - SYN: synchronize sequence numbers, only sent in first packet for both ends
    - FIN: last packet from sender

### Address Resolution Protocol
- Type: `0x08` `0x06` - ARP 
- Packet Structure
    ```
    2 bytes - Hardware Type
    2 bytes - Protocol Type
    1 byte  - Hardware Address Length
    1 byte  - Protocol Address Length
    2 bytes - Operation
    6 bytes - Sender Hardware Address
    4 bytes - Sender Protocol Address
    6 bytes - Target Hardware Address
    4 bytes - Target Protocol Address
    ```
    - Convert from Protocol Type to Hardware Type
    - Operation: `who-has: 00 01` `is-at: 00 02`

### CIDR Notation (Classless Inter-Domain Routing)
- An IP address allocation method that improves data routing efficiency on the Internet.
- An IP address has 2 parts:
    1. Network address --> network's unique identifier
    2. Host address --> host identifier on the network
- Classful addresses:
    - has fixed length for addresses
    - the number of bits allocated to network and host portions are fixed
    - IPv4: 32 bits, 4 bytes
    - Three classes of IPv4 addresses:
        1. Class A: 8 bit network
            -  For example, consider 44.0.0.1, where 44 is the network address and 0.0.1 is the host address.
        2. Class B: 16 bit network
            - For example, consider 128.16.0.2, where 128.16 is the network address and 0.2 is the host address.
        3. Class C: 24 bit network
            - For instance, consider 192.168.1.100, where 192.168.1 is the network address and 100 is the host address.
- Classless addresses
    - Uses *variable length subnet masking* (VLSM) to alter the ratio between network and host adresses
    - A *subsubet mask* returns the network's address value from IP address by turning host address to zeros.
    - A *CIDR IP address* appends a suffix value stating the **number of network address prefix bits** to a normal IP address.
        - For example, 192.0.2.0/24 is an IPv4 CIDR address where the first 24 bits, or 192.0.2, is the network address. 



        



## Cryptography

Alice <-------> Mallory <-------> Bob

We might have to send data through some third party, either malicious or just the Internet.

| CIA | Property 
| --- | -----------
| Confidentiality | Mallory can't view the contents of the data. The data is secret.
| Integrity | Mallory can't change the data. The data remained the same throughout the route.
| Authenticity | It is in fact Alice who sent the data to Bob. Mallory did not send the data. The data is sent by the expected sender.

Cryptography guarantees the properties of CIA.

### One-time-pad
- Encrpytion:
    1. Randomly generate a key
        - equal probability each bit is 0 or 1
    2. XOR each bit of plaintext with key
        - equal probability each bit is flipped
    - ciphertext will be complete gibberish
    - length of key must be >= length of plaintext
- Decryption:
    - XOR each bit of ciphertext with key
    - XOR is its own inverse
    - $(p \oplus k) \oplus k = p \oplus (k \oplus k) = p \oplus 0 = p$
- Flaws:
    - Frequency analysis exploit on repeating keys
    - If we can securely transfer key and key is as long as plaintext, why not just send plaintext?

### PROBLEM: 
- How can I securely get the key from Alice to Bob?
- If the key is just as long as the plaintext, why don't I just send the plaintext instead?
- In order to securely communicate with someone, I have to securely exchange a key. How is this possible?

### Solution: Diffie-Hellman Key Exchange
1. Generate `p`, `g`, where `p` prime and `g` primitive root mod `p`
2. Choose `a`, send `A = g^a % p`
3. Choose `b`, send `B = g^b % p`
4. `s = B^a % p` and `s = A^b % p`
- This works because of the Discrete Log Problem. Finding `a` and `b` is extremely difficult, whereas calculating `s` is very easy.

### Encyption Properties
- Confusion
    - Small change in key dramatically changes ciphertext
- Diffusion
    - Small change in plaintext dramatically changes ciphertext

### Advanced Encryption Standard (AES)
- substitution-permutation network
- satisfies confusion and diffusion
- key sizes: 128 / 192 / 256 bits
- block size: 128 bits, 16 bytes
- encrypts **exactly** 128 bits of plaintext to **exactly** 128 bits of ciphertext

**What happens if we only have 13 bytes of plaintext to encrypt?**
- Pad with null bytes?
    - No! Then we don't know what null bytes were intentional or padded.
- Solution: **PCK #7**
    - append number of bytes padded to the end
    - Ex: if 3 bytes were added, append 030303 to end of plaintext

**What happens if we have more than 16 bytes?**
- Solution: **Electronic Codebook** (ECB)
    - Pad out to a multiple of 16 bytes
    - split plaintext into blocks of 16 bytes
- **!! PROBLEM with ECB !!**

    - *ECB Penguin*: If plaintext data has a lot of similar or repeating blocks, the ciphertext blocks will also be similar or repeating. This destroys the *CONFIDENTIAL* property.

    - Solution: **Cipher Block Chaining** (CBC)
        - XOR first block of plaintext with an initialization vector and encrypt result.
        - XOR previous block's ciphertext with current block of plaintext and encrypt result.
        - Flaw: 
            - This is very slow! Each block of plaintext relies on the previous block's ciphertext. Thus encryption is sequential, meaning SLOW!

    - Solution: **Counter** (CTR)
        - Generate a random 16 byte value, called a *nonce*.
        - Add 1 to the *nonce* for next block.
            - Add 2 to the *nonce* for the next next block.
                - And 3 to the *nonce* for the block after that.
                    - And so on...
        - Encrypt the *nonce* for each block.
        - XOR the encrypted value with plaintext for each block.
        - This encryption and XOR can all be done in parallel, thus FAST!

### Asymmetric Encryption
- Symmetric - key for both encryption and decryption
- Asymmetric - public key for encryption, private key for decryption

### Rivest-Shamir-Adleman (RSA)
![RSA](/pwncollege/images/rsa.png)

- This uses Euler's Theorem.
- <$e, n$> is the public key.
- <$d, n$> is the private key.
- $m$ is plaintext.
- $m^e$ is ciphertext.
- This works because prime factorization is very difficult, especially for large numbers.

### RSA Key Generation
1. Choose $p,q$
2. $n=pq$
3. $\phi(n) = (p-1)(q-1)$
4. Choose $e$ such that $gcd(e, \phi(n)) = 1$. Common for $e=65537$.
5. $d \equiv e^{-1} \ (mod \ \phi(n))$

- RSA Encryption: $c \equiv m^e \ (mod \ n)$
- RSA Decryption: $m \equiv c^d \ (mod \ n)$
- RSA Signing: $s \equiv m^d \ (mod \ n)$
- RSA Verification: $m \equiv s^e \ (mod \ n)$

### Hashing
- message ---> hash function ---> hash value
- Hashing is one way.
- Hashing Resistance Properties
    1. Pre-image resistance
        - Given hash value $h$, it should be difficult to find message $m$ such that $h$ = hash($m$).
        - Given my hash value, no one should be able to find a hash collision easily.
    2. Second pre-image resistance
        - Given message $m_1$, it should be difficult to find different message $m_2$ such that hash($m_1$) = hash($m_2$).
        - Given my message, no one should be able to find a hash collision easily. 
    3. Collision resistance
        - It should be difficult to find messages $m_1, m_2$ such that hash($m_1$) = hash($m_2$). 
        - Given any messages, no one should be able to find a hash collision easily.
- Applications of hashing:
    - SHA256
    - Password hashing with salt
    - Proof of work
        - There is a challenge and response hashed together such that the hash value starts with a given prefix.
        - Used in bitcoin mining

### Trust
**Diffie-Hellman Key Exchange Problem**
- What if Mallory is an active participant, instead of a passive listener?
- Then Mallory can perform the key exchange HERSELF and she will know the keys for both Alice and Bob.
- Now Mallory can intercept their messages and decrypt it with the respective key, read it, encrypt it with the respective key, and send it to the recipient.
- So there is no secure communication at all. THIS IS BAD!

The same problem occurs with RSA. Mallory can switch out the public key with Mallory's own public key.

**How can we trust the keys given to us?**

**Solution: Trust**
- We need a Root of Trust.
- The Root of Trust is the OS.
    - The OS figures out who else we can trust.
        - These trustees figure out who else we can trust.
- There is a network of trust starting from the Root of Trust.

**What is the process of learning who we can trust?**

```c
Certificate
{
    "name": str,
    "key": {
        "e": int,
        "n": int,
    },
    "signer": root
}
```

Hashing Certificate Data
- Certificate ---> Hash Function ---> Hash Value

Signing Certificate Data
- Hash Value ---> Signed by Root of Trust (RSA Decrypt) ---> Signature

Certificate Verification
- Certificate ---> Hash ---> X
- Signature ---> RSA (Encrypt) ---> Y

If X and Y are equal, then we can trust the public key in the certificate. This is because the Root of Trust says this is the actual public key and I trust the Root of Trust.

## Web Security
One application of web security is the prevention of random people from robbing your bank acount online.

- Web **Client** Security Considerations
    - Recieve arbitrary data from some remote server
    - Some things this data might influence client to do:
        1. Make additional HTTP requests to other servers
        2. Run arbitrary Javascript
- Web **Server** Security Considerations
    - Recieve arbitrary data from some remote client
    - Some things this data might influence server to do:
        1. Access or modify database
        2. Interact with server system
        3. Influence other web clients

### Injection
- Command
    ```bash
    system("TZ=`whoami` date")
    execve("/bin/sh", ["sh", "-c", "TZ=`whoami` date"], {...})
    execve("/usr/bin/whoami", ["whoami"], {...})
    execve("/usr/bin/date", ["date"], {"TZ": "root"})
    ```
    ```bash
    system("TZ=; whoami # date")
    execve("/bin/sh", ["sh", "-c", "TZ=; whoami # date"], {...})
    execve("/usr/bin/whoami", ["whoami"], {...})
    ```
- HTML
    ```HTML
    html("<p>Hello, <script>alert(1)</script>!</p>")
    ```
    - A user sending data to a web server, for the response to only come back to the user is a futile attack. The user is only "attacking" the user.
    - When this injection becomes dangerous is when we are able to affect other users with our data, meaning we are able to run arbitrary Javascript on their system.
- SQL
    ```SQL
    ' or 1=1 --
    ```
    - A solution to this is to use `?`, which parses first, then fills in the data.
- Stack Overflow ret2win

### Same-Origin Policy
- The policy the browser uses to decide how to handle requests and responses to different origins.
- HTTP URL
    - `scheme://host:port/path?query#fragment`
- Origin
    - `(scheme, host, port)`
- Sending HTTP Requests
    - Same origin - anything goes
    - Cross origin - Simple Requests allowed
- Reading HTTP Responses
    - Same origin - anything goes
    - Cross origin - HTML-Embeds allowed
- Effective Top-Level Domains + 1 = Site
- Same-Site Cookie Attribute
    - SameSite = None: Cookie is sent in cross-site requests
    - SameSite = Lax: Cookie is sent in cross-site top-level navigation GET requests
    - SameSite = Strict: Cookie is not sent in cross-site requests
- Domain Cookie Attribute
    - Cookie is sent in requests to specified domain and any subdomains if specified
    - Otherwise only sent to setting host
- Path Cookie Attribute
    - Cookie is sent in requests to the path and any other subpath
- Cross-Origin Resource Sharing (CORS)
    - When making a non-simple request in a browser, the browser checks if it is allowed to make such a request.