# 01 Compatibility 

#### getting started 

[video](https://www.youtube.com/watch?v=t-XmYt2z5S8)  [website](https://docs.aws.amazon.com/enclaves/latest/user/getting-started.html) [blog](https://aws.amazon.com/cn/blogs/china/aws-nitro-enclaves-isolated-ec2-environments-to-process-confidential-data/)

##### step 1 launch instances

1. sign in to the console -- ec2
2. launch a new instance
3. (choose AMI) choose Amazon Linux 2 AMI Kernel 5.10 ami-001089eb624938d9f
4. (choose an Instance Type) choose m5.xlarge
5. (configure instance) Advance Details Enclave -- Enable
6. Then review and launch!

##### step2 install nitro-cli(via ssh)

[website](https://docs.aws.amazon.com/enclaves/latest/user/nitro-enclave-cli-install.html)

```
sudo yum update -y
sudo amazon-linux-extras install aws-nitro-enclaves-cli -y
sudo yum install aws-nitro-enclaves-cli-devel python3 git -y
sudo pip3 install boto3 requests
sudo usermod -aG ne $USER
sudo usermod -aG docker $USER
```

modify pre-allocated memory in `/etc/nitro_enclaves/allocator.yaml` to 4000MB

```
sudo systemctl start nitro-enclaves-allocator.service && sudo systemctl enable nitro-enclaves-allocator.service
sudo systemctl start docker && sudo systemctl enable docker
```

reboot the instance

##### step 3 build the enclave (cpp hello world -- test1)

```
docker build . -t test1
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test1:latest --output-file test1.eif
nitro-cli run-enclave --cpu-count 2 --memory 3000 --eif-path test1.eif --debug-mode
nitro-cli describe-enclaves
nitro-cli console --enclave-id xxxxxxxxxxxxxxxxxx
nitro-cli terminate-enclave --enclave-id xxxxxxxxxx
```

##### step 3 build the enclave (c hello world -- test2)

```
docker build . -t test2
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test1:latest --output-file test2.eif
nitro-cli run-enclave --cpu-count 2 --memory 3000 --eif-path test2.eif --debug-mode
nitro-cli describe-enclaves
nitro-cli console --enclave-id xxxxxxxxxxxxxxxxxx
nitro-cli terminate-enclave --enclave-id xxxxxxxxxx
```

##### step 3 build the enclave (java hello world -- test3)

```
docker build . -t test3
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test3:latest --output-file test3.eif
nitro-cli run-enclave --cpu-count 2 --memory 3000 --eif-path test3.eif --debug-mode
nitro-cli describe-enclaves
nitro-cli console --enclave-id xxxxxxxxxxxxxxxxxx
nitro-cli terminate-enclave --enclave-id xxxxxxxxxx
```

##### step 3 build the enclave (python hello world -- test4)  need at least 3508MB

```
docker build . -t test4
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test4:latest --output-file test4.eif
nitro-cli run-enclave --cpu-count 2 --memory 4000 --eif-path test4.eif --debug-mode
nitro-cli describe-enclaves
nitro-cli console --enclave-id xxxxxxxxxxxxxxxxxx
nitro-cli terminate-enclave --enclave-id xxxxxxxxxx
```

##### step 3 build the enclave (Nodejs hello world -- test5) --TODO

[ref1](https://flaviocopes.com/docker-node-container-example/) [ref2](https://nodejs.org/en/docs/guides/nodejs-docker-webapp/)

```
curl -sL https://rpm.nodesource.com/setup_14.x | sudo bash -
sudo yum install nodejs –y
npm init -y
#npm install express
docker build . -t test5
docker image ls
docker run -d -p 3000:3000 -it test5
```

then can use `curl http://localhost:3000 ` via ssh to check

```
nitro-cli build-enclave --docker-dir ./ --docker-uri test5:latest --output-file test5.eif
nitro-cli run-enclave --cpu-count 2 --memory 4000 --eif-path test5.eif --debug-mode
nitro-cli describe-enclaves
nitro-cli console --enclave-id xxxxxxxxxxxxxxxxxx
nitro-cli terminate-enclave --enclave-id xxxxxxxxxx
```

##### step 3 build the enclave (golang hello world -- test6)

```
docker build . -t test6
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test6:latest --output-file test6.eif
nitro-cli run-enclave --cpu-count 2 --memory 3000 --eif-path test6.eif --debug-mode
nitro-cli describe-enclaves
nitro-cli console --enclave-id xxxxxxxxxxxxxxxxxx
nitro-cli terminate-enclave --enclave-id xxxxxxxxxx
```

##### step 3 build the enclave (php hello world -- test7)

[ref3](http://richardn.ca/2019/01/15/running-a-php-site-with-docker/)

```
docker build . -t test7
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test7:latest --output-file test7.eif
nitro-cli run-enclave --cpu-count 2 --memory 3000 --eif-path test6.eif --debug-mode
nitro-cli describe-enclaves
nitro-cli console --enclave-id xxxxxxxxxxxxxxxxxx
nitro-cli terminate-enclave --enclave-id xxxxxxxxxx
```









### test for hello world

| #     | language                                                     |
| ----- | ------------------------------------------------------------ |
| test1 | cpp                                                          |
| test2 | c                                                            |
| test3 | java<br />**attention! cannot use FROM amazonlinux ; RUN yum install java-devel -y** <br />just use FROM java:8 |
| test4 | Python                                                       |
| test5 | JavaScript/NodeJS **TODO1**                                  |
| test6 | Go                                                           |
| test7 | PHP                                                          |

