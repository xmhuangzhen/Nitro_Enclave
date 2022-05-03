# Nitro Enclave

The goal of this project is to test different aspects of AWS Nitro Enclave, including compability, performance, persistence, AWS Certificate Manager(ACM) and Key Management Service(KMS).


### getting started

Before building the enclave, we recommend you to follow the [prerequisite](/prerequisite.md) to setup environment first.


### Compatibility

Description: Run code in a variety of languages inside a Nitro enclave to test compatibility

Result: 
- [C++](/01Compatibility/test1/), [C](/01Compatibility/test2/), [Java](/01Compatibility/test3/), [Python](/01Compatibility/test4/), [Golang](/01Compatibility/test6/) can run inside a Nitro Enclave with repeatedly printing "Hello World!".
- [Nodejs](/01Compatibility/test5/) and [PHP](/01Compatibility/test7/) cannot work well currently.

You can see the [record](/01Compatibility/test_record.md) for more details.

### Performance

Description: What are the performance overheads in Nitro Enclave?

Result: There is no significant difference in the time spent running a docker inside and outside the enclave. In addition, the docker runs inside the enclave is a little bit faster than outside. You can see the [record](/02Performance/test_record.md) for more details.

### Persistence

Description: Nitro does not have a built-in way to persist data, but can a secure persistence layer easily be created through some combination of KMS and S3?

Result: It can be built in the following steps: (1) create a "KMS" key in nitro enclave --> (2) encrypt the objects in the enclave --> (3) transmit the objects to the parent instance --> (4) parent instance upload it to s3. You can see the [file](/03Persistence/record.md) for more details.

### AWS Certificate Manager(ACM)

Description: Can you connect to the inside of a Nitro enclave via SSL/TLS? Can ACM be configured to ONLY allow SSL/TLS certificates to be accessed within Nitro enclaves?

Result: AWS Certificate Manager (ACM) for Nitro Enclaves allows you to use public and private SSL/TLS certificates with your web applications and web servers running on Amazon EC2 instances with AWS Nitro Enclaves. SSL/TLS certificates are used to secure network communications and to establish the identity of websites over the internet, as well as resources on private networks. You can see the [file](/04ACM/record.md) for more details.

###  Key Management Service(KMS)

Description: Can KMS keys have key policies that make them only accessible within Nitro? Is there any way to later change or bypass the key policy to access a key outside of Nitro?

Result: This part demonstrates how cryptographic attestation can be used to protect the privacy of sensitive data. Cryptographic attestation can be used to enhance the isolation of sensitive data processing workloads in a Nitro Enclave. You can see the [file](/05KMS/record.md) for more details.

