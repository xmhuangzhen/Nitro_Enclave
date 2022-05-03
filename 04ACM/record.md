# 04 ACM

This tutorial is based on the official[user guide](https://docs.aws.amazon.com/zh_cn/enclaves/latest/user/nitro-enclave-refapp.html).

#### step0 Register a new domain using Route53 

1. Sign in to the AWS Management Console and open the Route 53 console at https://console.aws.amazon.com/route53/.
2. If you're new to Route 53, choose Get started. If you're already using Route 53, in the navigation pane, choose Registered domains.
3. Choose Register domain, and specify the domain that you want to register: Enter the domain name that you want to register, and choose Check to find out whether the domain name is available. If the domain is available, choose Add to cart. The domain name appears in your shopping cart. In the shopping cart, choose the number of years that you want to register the domain for.
4. Choose Continue.
5. On the Contact Details for Your n Domains page, enter contact information for the domain registrant, administrator, and technical contacts. 
6. Choose Continue.
7. Choose whether you want us to automatically renew your domain registration before the expiration date.
8. Choose Complete Purchase.

#### step 1 create the AWS Certificate Manager certificate using the console

1. Sign in to the AWS Management Console and open the ACM console at https://console.aws.amazon.com/acm/home. Choose Request a certificate.
2. In the Domain names section, type your domain name.
3. To add another name, choose Add another name to this certificate and type the name in the text box. This is useful for protecting both a bare or apex domain (such as example.com) and its subdomains such as *.example.com).
4. In the Select validation method section, choose either DNS validation or Email validation, depending on your needs.
5. In the Tags page, you can optionally tag your certificate.
6. After the request is processed, the console returns you to your certificate list, where information about the new certificate is displayed.


#### step2 launch a parent instance

1. Open the AWS Certificate Manager for [Nitro Enclaves page](https://aws.amazon.com/marketplace/pp/prodview-f4gcl7narsmle) in the AWS Marketplace.

2. Find the ACM for Nitro Enclaves AMI for your Region, and note the AMI ID. You need the AMI ID for the next step.

3. Launch the instance using the AMI from the AWS Marketplace and enable it for Nitro Enclaves using the following command.

```
aws ec2 run-instances --image-id ami-00d96e5ee00daa484 --count 1 --instance-type m5.xlarge --key-name your_key_name --enclave-options 'Enabled=true'
```

#### step3 prepare IAM role 

To grant the instance permission to use the ACM certificate, you must create an IAM role with the required permissions. The IAM role is later attached to the instance and the ACM certificate.

Create a JSON file named acm-role and add the following policy statement.
```
{
   "Version":"2012-10-17",
   "Statement":[
      {
         "Effect":"Allow",
         "Principal":{
            "Service":"ec2.amazonaws.com"
         },
         "Action":"sts:AssumeRole"
      }
   ]
}
```
Use the `create-role` command to create a role named acm-role, and specify the path to the JSON policy file.
```
$ aws iam create-role --role-name acm-role --assume-role-policy-document file://acm-role.json
```

After you have created the role, make a note of the role ARN, as you'll need it in the next step.


#### step4 associate with ACM certificate 
Attach the IAM role that you created in the previous step to the ACM certificate. To do this, use the associate-enclave-certificate-iam-role command, and specify the ARN of the role to attach, and the ARN of the certificate to attach it to.

```
$ aws ec2 --region region associate-enclave-certificate-iam-role --certificate-arn certificate_ARN --role-arn role_ARN
```

For example

```
$ aws ec2 --region us-east-1 associate-enclave-certificate-iam-role --certificate-arn arn:aws:acm:us-east-1:123456789012:certificate/d4c3b2a1-e5d0-4d51-95d9-1927fEXAMPLE --role-arn arn:aws:iam::123456789012:role/acm-role
```

Example output
```
{

"CertificateS3BucketName": "aws-ec2-enclave-certificate-us-east-1",
"CertificateS3ObjectKey": "arn:aws:iam::123456789012:role/acm-role/arn:aws:acm:us-east-1:123456789012:certificate/d4c3b2a1-e5d0-4d51-95d9-1927fEXAMPLE",
"EncryptionKmsKeyId": "a1b2c3d4-354d-4e51-9190-b12ebEXAMPLE"
}
```

After running the command, make a note of `CertificateS3BucketName` and `EncryptionKmsKeyId`, as you'll need them for the next step.





& grant role permissions (only need once)

#### step3 associate
```
aws ec2 --region us-east-1 associate-iam-instance-profile --instance-id instance_id --iam-instance-profile Name=acm-instance-profile
```

#### step4 config in the parent instance

#### step5 test
curl https://domain_name


#### reference 

[register a new domain](https://docs.aws.amazon.com/Route53/latest/DeveloperGuide/domain-register.html)

[request a public certificate](https://docs.aws.amazon.com/acm/latest/userguide/gs-acm-request-public.html)


#### misc
- notice the inbound rules of the parent instance(ssh port 22 & tcp port 443 need to be open)
