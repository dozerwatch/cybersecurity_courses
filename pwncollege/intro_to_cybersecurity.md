# Introduction to Cybersecurity
- [Building A Web Server](#building-a-web-server)
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
    

## Building A Web Server
- CPUs contain registers, have a small amount of memory, and can perform a lot of operations.
- We are **not** allowed to manipulate hardware directly, instead we have to talk with the **OS** using `syscalls`.
- The **kernal memory** keeps track of the state of processes.
    - located at the bottom of memory (high addresses)
    - processes are just **data** in kernal memory
    - `syscalls` manipulate kernal memory
- `struct task_struct` is a blob is data managing the state of a process.
- `struct task_struct *current` is a **global** variable that keeps track of the **current executing process**.
- `socket` creates an endpoint for communication
- `bind` assigns an address to a socket
    - the address follows the structure
        ```C
        struct sockaddr_in {
            uint16_t sa_family;
            uint8_t sa_data[14];
        };
        ```
    - `uint16_t` represents 2 bytes
    - `uint8_t` represents 1 byte
    - the address structure for **Internet** is
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
- Networking likes to work in **big-endian**.
- `listen` listens for incoming connection requests and puts them into a backlog queue.
- `accept` extracts first connection request on queue and creates a new connected socket, returning a new FD for it.
- `fork` creates a new child process by **duplicating** the calling parent process
    - on success, `PID` of child is returned to the parent and `0` is returned to child
    - both processes will run the same code

## Intercepting Communication
![dynamic network](/pwncollege/images/dynamic_network.png)

- There are three different ways to intercept communication:
    1. At the source
    2. Middle-man
    3. At the destination

### Ethernet
- physically connected
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
- Organizations use CIDR to allocate IP addresses flexibly and efficiently in their networks.
- An IP address has 2 parts:
    1. Network address --> networ's unique identifier
    2. Host address --> host identifier on the network
- Classful addresses:
    - has fixed length for addresses
    - the number of bits allocated to network and host portions are fixed
    - IPv4: 32 bits
    - Three classes of IPv4 addresses:
        1. Class A: 8 bit network
        2. Class B: 16 bit network
        3. Class C: 24 bit network 
- Classless addresses
    - Uses variable length subnet masking (VLSM) to alter the ratio between network and host adresses
        - A subsubet mask returns the network's address value from IP address by turning host address to zeros.

## Cryptography

Alice <-------> Mallory <-------> Bob

- We might have to send data through some third party, either malicious or just the Internet
    | CIA | Property 
    | --- | -----------
    | Confidentiality | Mallory can't view the contents of the data. The data is secret.
    | Integrity | Mallory can't change the data. The data remained the same throughout the route.
    | Authenticity | It is in fact Alice who sent the data to Bob. Mallory did not send the data. The data is sent by the expected sender.
- Cryptography guarantees the properties of CIA.

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

### Encyption Properties
- Confusion
    - Small change in key dramatically changes ciphertext
- Diffusion
    - Small change in plaintext dramatically changes ciphertext

### Advanced Encryption Standard (AES)
- satisfies confusion and diffusion
- key sizes: 128 / 192 / 256 bits
- block size: 128 bits, 16 bytes
- encrypts exactly 128 bits of plaintext to exactly 128 bits of ciphertext

**What happens if we only have 13 bytes of plaintext to encrypt?**
- Pad with null bytes?
    - No! Then we don't know what null bytes were intentional or padded
    - Solution: PCK #7
        - append number of bytes padded to the end
        - if 3 bytes were added, append 030303 to end of plaintext

**What happens if we have more than 16 bytes?**
- Solution: Electronic Codebook (ECB)
    - Pad out to a multiple of 16 bytes
    - split plaintext into blocks of 16 bytes

**!! PROBLEM with ECB !!**
- If plaintext data has a lot of similar or repeating blocks, the ciphertext blocks will also be similar or repeating.
- ECB Penguin
- Solution: Cipher Block Chaining (CBC)
    - XOR previous block's ciphertext with plaintext and encrypt this
    - XOR first block of plaintext with an initialization vector
    - This is very SLOW! Each block of plaintext relies on the previous block's ciphertext. Thus encryption is sequential, meaning slow!
- Solution: Counter (CTR)
    - Generate a random 16 byte value
    - Add 1 to this value for next block and so on
    - Encrypt this value
    - XOR the encrypted value with plaintext
    - This encryption and XOR can all be done in parallel, thus FAST!

#### PROBLEM
- How can I securely get the key from Alice to Bob?
- If the key is just as long as the plaintext, why don't I just send the plaintext instead?

### Diffie-Hellman Key Exchange
1. Generate `p`, `g`, where `p` prime and `g` primitive root mod `p`
2. Choose `a`, send `A = g^a % p`
3. Choose `b`, send `B = g^b % p`
4. `s = B^a % p` and `s = A^b % p`
- This works because of the Discrete Log Problem. Finding `a` and `b` is extremely difficult, whereas calculating `s` is very easy.

### Asymmetric Encryption
- Symmetric - key for both encryption and decryption
- Asymmetric - public key for encryption, private key for decryption
- **Fermat's Little Theorem**
    ![Fermat's Little Theorem](/pwncollege/images/fermat_little_theorem.png)
- **Euler's Theorem**
    ![Euler's Theorem](/pwncollege/images/eulers_theorem.png)

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
        - There is a challenge and response hashed together such that the hash value starts with a given prefix
        - Used in bitcoin mining

### Trust
- **Diffie-Hellman Key Exchange Problem**
    - What if Mallory is an active participant, instead of a passive listener?
    - Then Mallory can perform the key exchange HERSELF and she will know the keys for both Alice and Bob.
    - Now Mallory can intercept their messages and decrypt it with the respective key, read it, encrypt it with the respective key, and send it to the recipient.
    - So there is no secure communication at all. THIS IS BAD!
- The same problem occurs with RSA
    - Mallory can switch out the public keys.

How can we trust that the keys given were actually by who we intended.

**Solution: Trust**
- We need a Root of Trust
- The Root of Trust is the OS
    - The OS figures out who else we can trust
        - These trustees figure out who else we can trust
- There is a network of trust starting from the Root of Trust

What is the process of learning who we can trust?

**Hashing Certificate Data**

```md
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
- Certificate ---> Hash Function ---> Hash Value

**Hashing Certificate Data**
- Hash Value ---> Sign (RSA Decrypt) ---> Signature

**Certificate Verification**
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