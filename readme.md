# Nitro Enclave

The goal of this project is to test different aspects of AWS Nitro Enclave, including compability, performance, persistence, AWS Certificate Manager(ACM) and Key Management Service(KMS).

</br>


### Get Started


### Compatibility

Description: Run code in a variety of languages inside a Nitro enclave to test compatibility

Result: [C++](/01Compatibility/test1/), [C](/01Compatibility/test2/), Java, Python, Golang can run in
| test number | language | result |
| ----------- | -------- | ------ |
| test1       | cpp      | yes    |
| test2       | c        | yes    |
| test3       | java     | yes    |
| test4       | python   | yes    |
| test5       | NodeJs   | no     |
| test6       | Go       | yes    |
| test7       | PHP      | no     |



### Performance

What are the performance overheads Nitro incurs with respect to memory, computation, networking? What degree of parallelism is supported?

**Persistence**: Nitro does not have a built-in way to persist data, but can a secure persistence layer easily be created through some combination of KMS and S3?

**ACM**: Can you connect to the inside of a Nitro enclave via SSL/TLS? Can ACM be configured to ONLY allow SSL/TLS certificates to be accessed within Nitro enclaves?

**KMS**: Can KMS keys have key policies that make them only accessible within Nitro? Is there any way to later change or bypass the key policy to access a key outside of Nitro?


</br>
</br>

## result

##### 01 compatibility


##### 02 Performance

result: no obvious difference inside & outside enclave



[attestation platform](https://trust.multifactor.com/#/nitro)  [(code)](https://github.com/multifactor/trust-center)
