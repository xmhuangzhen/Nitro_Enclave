# Prerequisite

This tutorial is based on the [official guide](https://docs.aws.amazon.com/enclaves/latest/user/getting-started.html), the [video](https://www.youtube.com/watch?v=t-XmYt2z5S8) and the [blog](https://aws.amazon.com/cn/blogs/china/aws-nitro-enclaves-isolated-ec2-environments-to-process-confidential-data/).

## step 1 launch instances

1. sign in to the console of amazon and choose ec2
2. launch a new instance
3. (choose AMI) choose Amazon Linux 2 AMI Kernel 5.10 ami-001089eb624938d9f
4. (choose an Instance Type) choose m5.xlarge
5. (configure instance) Advance Details Enclave -- Enable
6. Then review and launch!

## step2 install nitro-cli(via ssh)

1. connect to the instance through ssh by `ssh -i key_pair_file_path ec2-user@the_instance_ip`.
2. install nitro-cli
```
sudo yum update -y
sudo amazon-linux-extras install aws-nitro-enclaves-cli -y
sudo yum install aws-nitro-enclaves-cli-devel python3 git -y
sudo pip3 install boto3 requests
sudo usermod -aG ne $USER
sudo usermod -aG docker $USER
```

3. modify pre-allocated memory in `/etc/nitro_enclaves/allocator.yaml` to 5000MB
```
sudo systemctl start nitro-enclaves-allocator.service && sudo systemctl enable nitro-enclaves-allocator.service
sudo systemctl start docker && sudo systemctl enable docker
```
4. reboot the instance
