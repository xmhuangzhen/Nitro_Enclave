# Nitro Enclave



**Compatibility**: Try running code in a variety of languages (C/C++, Java, Python, JavaScript/NodeJS, Go, PHP) inside a Nitro enclave to test compatibility

**Performance**: What are the performance overheads Nitro incurs with respect to memory, computation, networking? What degree of parallelism is supported?

**Persistence**: Nitro does not have a built-in way to persist data, but can a secure persistence layer easily be created through some combination of KMS and S3?

**ACM**: Can you connect to the inside of a Nitro enclave via SSL/TLS? Can ACM be configured to ONLY allow SSL/TLS certificates to be accessed within Nitro enclaves?

**KMS**: Can KMS keys have key policies that make them only accessible within Nitro? Is there any way to later change or bypass the key policy to access a key outside of Nitro?