# 02 performance

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

##### step 3 build the enclave (cpp sha256 -- test1)

[ref1](https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c/10632725)

```
sudo yum install openssl-devel gcc-c++ -y 

docker build . -t test1
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test1:latest --output-file test1.eif
nitro-cli run-enclave --cpu-count 2 --memory 5000 --eif-path test1.eif --debug-mode
nitro-cli describe-enclaves
nitro-cli console --enclave-id xxxxxxxxxxxxxxxxxx
nitro-cli terminate-enclave --enclave-id xxxxxxxxxx
```

##### step 3 build the enclave (cpp addition -- test2)

```
sudo yum install openssl-devel gcc-c++ -y 
docker build . -t test2
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test2:latest --output-file test2.eif
nitro-cli run-enclave --cpu-count 2 --memory 5000 --eif-path test2.eif --debug-mode
nitro-cli describe-enclaves
nitro-cli console --enclave-id xxxxxxxxxxxxxxxxxx
nitro-cli terminate-enclave --enclave-id xxxxxxxxxx
```











### test for hello world

| test number | inside/outside    | implementation                             |
| ----------- | ----------------- | ------------------------------------------ |
| test1       | 388,837 / 374,154 | number of sha256 operations in 1000ms      |
| test2       | 21961ms / 21782ms | time 10,000,000,000 times addition (ans++) |





