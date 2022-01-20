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

modify pre-allocated memory in `/etc/nitro_enclaves/allocator.yaml` to 3000MB

```
sudo systemctl start nitro-enclaves-allocator.service && sudo systemctl enable nitro-enclaves-allocator.service
sudo systemctl start docker && sudo systemctl enable docker
```

reboot the instance

##### step 3 build the enclave (cpp hello world)

```
docker build . -t test1
docker image ls
nitro-cli build-enclave --docker-dir ./ --docker-uri test1:latest --output-file test1.eif
nitro-cli run-enclave --cpu-count 2 --memory 3000 --eif-path test1.eif --debug-mode
nitro-cli describe-enclaves
nitro-cli console --enclave-id xxxxxxxxxxxxxxxxxx
nitro-cli terminate-enclave --enclave-id xxxxxxxxxx
```



### test for hello world

| #    | language |
| ---- | -------- |
| 1    | cpp      |

