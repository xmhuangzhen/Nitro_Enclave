# 01 Compatibility 

Before building the enclave, we recommend you to follow the [prerequisite](/prerequisite.md) first.

### step 3 build the enclave (cpp hello world -- test1)

```
docker build . -t test1
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test1:latest --output-file test1.eif
nitro-cli run-enclave --cpu-count 2 --memory 3000 --eif-path test1.eif --debug-mode
ENCLAVE_ID=$(nitro-cli describe-enclaves | jq -r ".[0].EnclaveID")
[ "$ENCLAVE_ID" != "null" ] && nitro-cli console --enclave-id ${ENCLAVE_ID}
[ "$ENCLAVE_ID" != "null" ] && nitro-cli terminate-enclave --enclave-id ${ENCLAVE_ID}
```

##### step 3 build the enclave (c hello world -- test2)

```
docker build . -t test2
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test1:latest --output-file test2.eif
nitro-cli run-enclave --cpu-count 2 --memory 3000 --eif-path test2.eif --debug-mode
ENCLAVE_ID=$(nitro-cli describe-enclaves | jq -r ".[0].EnclaveID")
[ "$ENCLAVE_ID" != "null" ] && nitro-cli console --enclave-id ${ENCLAVE_ID}
[ "$ENCLAVE_ID" != "null" ] && nitro-cli terminate-enclave --enclave-id ${ENCLAVE_ID}
```

##### step 3 build the enclave (java hello world -- test3)

```
docker build . -t test3
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test3:latest --output-file test3.eif
nitro-cli run-enclave --cpu-count 2 --memory 3000 --eif-path test3.eif --debug-mode
ENCLAVE_ID=$(nitro-cli describe-enclaves | jq -r ".[0].EnclaveID")
[ "$ENCLAVE_ID" != "null" ] && nitro-cli console --enclave-id ${ENCLAVE_ID}
[ "$ENCLAVE_ID" != "null" ] && nitro-cli terminate-enclave --enclave-id ${ENCLAVE_ID}
```

##### step 3 build the enclave (python hello world -- test4)  need at least 3508MB

```
docker build . -t test4
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test4:latest --output-file test4.eif
nitro-cli run-enclave --cpu-count 2 --memory 4000 --eif-path test4.eif --debug-mode
ENCLAVE_ID=$(nitro-cli describe-enclaves | jq -r ".[0].EnclaveID")
[ "$ENCLAVE_ID" != "null" ] && nitro-cli console --enclave-id ${ENCLAVE_ID}
[ "$ENCLAVE_ID" != "null" ] && nitro-cli terminate-enclave --enclave-id ${ENCLAVE_ID}
```

##### step 3 build the enclave (Nodejs hello world -- test5) -- failed

[ref1](https://flaviocopes.com/docker-node-container-example/) [ref2](https://nodejs.org/en/docs/guides/nodejs-docker-webapp/)

```
docker build . -t test5
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test5:latest --output-file test5.eif
nitro-cli run-enclave --cpu-count 2 --memory 4000 --eif-path test5.eif --debug-mode
nitro-cli describe-enclaves
ENCLAVE_ID=$(nitro-cli describe-enclaves | jq -r ".[0].EnclaveID")
[ "$ENCLAVE_ID" != "null" ] && nitro-cli console --enclave-id ${ENCLAVE_ID}
[ "$ENCLAVE_ID" != "null" ] && nitro-cli terminate-enclave --enclave-id ${ENCLAVE_ID}
```

##### step 3 build the enclave (golang hello world -- test6)

```
docker build . -t test6
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test6:latest --output-file test6.eif
nitro-cli run-enclave --cpu-count 2 --memory 3000 --eif-path test6.eif --debug-mode
ENCLAVE_ID=$(nitro-cli describe-enclaves | jq -r ".[0].EnclaveID")
[ "$ENCLAVE_ID" != "null" ] && nitro-cli console --enclave-id ${ENCLAVE_ID}
[ "$ENCLAVE_ID" != "null" ] && nitro-cli terminate-enclave --enclave-id ${ENCLAVE_ID}
```

##### step 3 build the enclave (php hello world -- test7) -- failed

[ref3](http://richardn.ca/2019/01/15/running-a-php-site-with-docker/)

```
docker build . -t test7
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test7:latest --output-file test7.eif
nitro-cli run-enclave --cpu-count 2 --memory 3000 --eif-path test6.eif --debug-mode
nitro-cli describe-enclaves
ENCLAVE_ID=$(nitro-cli describe-enclaves | jq -r ".[0].EnclaveID")
[ "$ENCLAVE_ID" != "null" ] && nitro-cli console --enclave-id ${ENCLAVE_ID}
[ "$ENCLAVE_ID" != "null" ] && nitro-cli terminate-enclave --enclave-id ${ENCLAVE_ID}
```


### test for hello world

| #     | language                                                     |
| ----- | ------------------------------------------------------------ |
| test1 | cpp                                                          |
| test2 | c                                                            |
| test3 | java<br />**attention! cannot use FROM amazonlinux ; RUN yum install java-devel -y** <br />just use FROM java:8 |
| test4 | Python                                                       |
| test5 | JavaScript/NodeJS                                   |
| test6 | Go                                                           |
| test7 | PHP                                                          |

[vsock](https://nitro-enclaves.workshop.aws/en/my-first-enclave/secure-local-channel.html)

