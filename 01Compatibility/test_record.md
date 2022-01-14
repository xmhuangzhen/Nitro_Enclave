# 01 Compatibility 

#### getting started 

[video](https://www.youtube.com/watch?v=t-XmYt2z5S8)  [website](https://docs.aws.amazon.com/enclaves/latest/user/getting-started.html)

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
sudo amazon-linux-extras install aws-nitro-enclaves-cli -y
sudo yum install aws-nitro-enclaves-cli-devel -y
sudo usermod -aG ne ec2-user
sudo usermod -aG docker ec2-user
```

reconnect to the instance

```
sudo systemctl start nitro-enclaves-allocator.service 
sudo systemctl enable nitro-enclaves-allocator.service
sudo systemctl start docker 
sudo systemctl enable docker
```

##### step 3 build the enclave (version 0 -- official docker hello-world)

```
docker pull hello-world
docker image ls
nitro-cli build-enclave --docker-uri hello-world:latest --output-file test2.eif
nitro-cli run-enclave --cpu-count 2 --memory 512 --eif-path test2.eif --debug-mode
nitro-cli describe-enclaves
```

# FAILED!!!



##### step 3 build the enclave (version 1 -- my cpp hello world)

copy the test1 folder to the instance, run 

```
sudo yum install gcc-c++ -y
g++ -o test1 test1.cpp
```

then get the output test1

```
docker build . -t test1
docker image ls
nitro-cli build-enclave --docker-uri test1:latest --output-file test1.eif
nitro-cli run-enclave --cpu-count 2 --memory 512 --eif-path test1.eif --debug-mode
nitro-cli describe-enclaves
```

# FAILED!!!



# 





### test for hello world

| #    | language |
| ---- | -------- |
| 1    | cpp      |

