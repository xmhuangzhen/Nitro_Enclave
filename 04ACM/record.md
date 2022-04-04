# 04 ACM

[user guide](https://docs.aws.amazon.com/zh_cn/enclaves/latest/user/nitro-enclave-refapp.html)

#### step0

[register a new domain](https://docs.aws.amazon.com/Route53/latest/DeveloperGuide/domain-register.html)

[request a public certificate](https://docs.aws.amazon.com/acm/latest/userguide/gs-acm-request-public.html)

#### step1 launch a parent instance
```
aws ec2 run-instances --image-id ami-00d96e5ee00daa484 --count 1 --instance-type m5.xlarge --key-name your_key_name --enclave-options 'Enabled=true'
```

#### step2 
prepare IAM role & associate with ACM certificate & grant role permissions (only need once)

#### step3 associate
```
aws ec2 --region us-east-1 associate-iam-instance-profile --instance-id instance_id --iam-instance-profile Name=acm-instance-profile
```

#### step4 config in the parent instance

#### step5 test
curl https://domain_name

#### misc
- notice the inbound rules of the parent instance(ssh & tcp443 need to be open)
