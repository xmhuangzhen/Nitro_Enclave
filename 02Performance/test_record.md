# 02 performance

Before building the enclave, we recommend you to follow the [prerequisite](/prerequisite.md) first. Meanwhile, the comparison between inside and outside the enclave are both running with docker.

### build the enclave (cpp sha256 -- test1)

[ref1](https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c/10632725)

```
sudo yum install openssl-devel gcc-c++ -y 

docker build . -t test1
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test1:latest --output-file test1.eif
nitro-cli run-enclave --cpu-count 2 --memory 5000 --eif-path test1.eif --debug-mode
ENCLAVE_ID=$(nitro-cli describe-enclaves | jq -r ".[0].EnclaveID")
[ "$ENCLAVE_ID" != "null" ] && nitro-cli console --enclave-id ${ENCLAVE_ID}
[ "$ENCLAVE_ID" != "null" ] && nitro-cli terminate-enclave --enclave-id ${ENCLAVE_ID}
```

### build the enclave (cpp addition -- test2)

```
sudo yum install openssl-devel gcc-c++ -y 
docker build . -t test2
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test2:latest --output-file test2.eif
nitro-cli run-enclave --cpu-count 2 --memory 5000 --eif-path test2.eif --debug-mode
ENCLAVE_ID=$(nitro-cli describe-enclaves | jq -r ".[0].EnclaveID")
[ "$ENCLAVE_ID" != "null" ] && nitro-cli console --enclave-id ${ENCLAVE_ID}
[ "$ENCLAVE_ID" != "null" ] && nitro-cli terminate-enclave --enclave-id ${ENCLAVE_ID}
```

#### build the enclave (python3 addition -- test2)

```
docker build . -t test2
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test3:latest --output-file test3.eif
nitro-cli run-enclave --cpu-count 2 --memory 5000 --eif-path test3.eif --debug-mode
ENCLAVE_ID=$(nitro-cli describe-enclaves | jq -r ".[0].EnclaveID")
[ "$ENCLAVE_ID" != "null" ] && nitro-cli console --enclave-id ${ENCLAVE_ID}
[ "$ENCLAVE_ID" != "null" ] && nitro-cli terminate-enclave --enclave-id ${ENCLAVE_ID}
```


### test for hello world

| test number | inside | outside    | operation                             |
| ----------- | --------|--------- | ------------------------------------------ |
| test1       |  |  | number of sha256 operations in 1000ms      |
| test2       |  |  | time 10,000,000,000 times addition (ans++) in c++ |
| test3       |  |  | time 10,000,000,000 times addition (ans++) in python |



#### raw data on test1 -- v1

| |outside(no docker) | outside(in docker gcc:latest) |outside(in docker amazonlinux)| inside (gcc:latest) | inside(amazonlinux)|
|--|--|--|--|
|1|367063|388307|375190|389620|375801|
|2|373416|388214|375116|389542|375567|
|3|373288|388258|375236|389531|375486|
|4|373320|388459|375138|389418|375481|
|5|373382|388441|374708|389648|375831|
|average|372094|388334|375078|389552|375633|


#### raw data on test2 --v1

|| outside(no docker) | inside (gcc:latest) | inside(amazonlinux)|
|--|--|--|--|
|1|21778|21963|21765|
|2|21778|21969|21765|
|3|21779|21969|21765|
|4|21777|21977|21764|
|5|21778|21981|21766|
|average|21778|21972|21765|

#### raw data on test3 --v1

|| outside(no docker) | inside (python:3) | inside(amazonlinux)|
|--|--|--|--|
|1|8.423|7.293|8.430|
|2|8.430|7.302|8.423|
|3|8.427|7.310|8.425|
|4|8.425|7.301|8.436|
|5|8.429|7.309|8.433|
|average|8.427|7.303|8.429|
