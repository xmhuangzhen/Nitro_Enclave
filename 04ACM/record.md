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


#### Step 5 Grant the role permission to access the certificate and encryption key
You must now grant the IAM role (acm-role) permission to do the following:

- Retrieve the ACM certificate from the Amazon S3 bucket returned in the previous step

- Perform kms:Decrypt using the AWS KMS key returned in the previous step

- Retrieve information about itself, including its path, GUID, and ARN.

Create a JSON file named acm-role-policies, add the following policy statement, and specify the values of CertificateS3BucketName and EncryptionKmsKeyId from the previous step.
```
{
  "Version": "2012-10-17",
  "Statement": [
    {
        "Effect": "Allow",
        "Action": [
        "s3:GetObject"
        ],
        "Resource": ["arn:aws:s3:::CertificateS3BucketName/*"]
    },
    {
        "Sid": "VisualEditor0",
        "Effect": "Allow",
        "Action": [
            "kms:Decrypt"
        ],
        "Resource": "arn:aws:kms:region:*:key/EncryptionKmsKeyId"
    },
    {
            "Effect": "Allow",
            "Action": "iam:GetRole",
            "Resource": "arn:aws:iam::123456789012:role/acm-role"
    }
  ]
}
```
Use the put-role-policy command to add the additional policies to the acm-role role, and specify the path to the JSON policy file.
```
$ aws iam put-role-policy --role-name acm-role --policy-name acm-role-policy --policy-document file://acm-role-policies.json
```

#### Step 6 Attach the role to the instance
You must attach the IAM role to the instance to give it permission to use the certificate.

Create a new instance profile named acm-instance-profile using the `create-instance-profile` command.
```
$ aws iam create-instance-profile --instance-profile-name acm-instance-profile
```
Example output
```
{
    "InstanceProfile": {
    "Path": "/",
     "InstanceProfileName": "acm-instance-profile",
    "InstanceProfileId": "ABCDUS6G56GWDIEXAMPLE",
    "Arn": "arn:aws:iam::123456789012:instance-profile/acm-instance-profile",
    "CreateDate": "2020-10-14T03:38:08+00:00",
    "Roles": []
    }
}
```
Add the acm-role that you created earlier to the acm-instance-profile that you just created. Use the `add-role-to-instance-profile` command.
```
$ aws iam add-role-to-instance-profile --instance-profile-name acm-instance-profile --role-name acm-role
```
Associate the instance profile with the instance that you launched previously. Use the `associate-iam-instance-profile` command and specify the instance profile to attach and the instance to attach it to.
```
$ aws ec2 --region region associate-iam-instance-profile --instance-id instance_id --iam-instance-profile Name=acm-instance-profile
```
Example output
```
{
    "IamInstanceProfileAssociation": 
    {
        "AssociationId": "iip-assoc-0a411083b4EXAMPLE",
        "InstanceId": "i-1234567890abcdef0",
        "IamInstanceProfile": 
        {
            "Arn": "arn:aws:iam::123456789012:instance-profile/acm-instance-profile",
            "Id": "ABCDUS6G56GWDIEXAMPLE"
        },
        "State": "associating"
    }
}
```


#### Step 7 Configure NGINX to use ACM for Nitro Enclaves
Configure the NGINX web server to use the ACM certificate.

To configure NGINX

1. SSH into the instance that you launched previously.

2. Rename the sample ACM for Nitro Enclaves configuration file from `/etc/nitro_enclaves/acm.example.yaml` to `/etc/nitro_enclaves/acm.yaml`.
```
$ sudo mv /etc/nitro_enclaves/acm.example.yaml /etc/nitro_enclaves/acm.yaml
```
3. Using your preferred text editor, open `/etc/nitro_enclaves/acm.yaml`. In the Acm section, for certificate_arn, specify the ARN of the certificate. Save and close the file.

4. Configure NGINX to use the pkcs11 SSL engine by setting the top-level ssl_engine directive. Using your preferred text editor, open `/etc/nginx/nginx.conf`. Add the following line below `pid /run/nginx.pid;`.
```
ssl_engine pkcs11;
```

Example
```
# For more information on configuration, see:
#   * Official English Documentation: http://nginx.org/en/docs/

user nginx;
worker_processes auto;
error_log /var/log/nginx/error.log;
pid /run/nginx.pid;

ssl_engine pkcs11;
```
5. Enable the TLS server and configure the server to use your certificate.

In `/etc/nginx/nginx.conf`, scroll to the bottom of the file and do the following:

- Uncomment all of the lines below Settings for a TLS enabled server.

- In the first block, for server_name, specify the host name, or the common name (CN), that you specified when you created the certificate.

- In the second block, remove the following lines.
```
ssl_certificate "/etc/pki/nginx/server.crt";
ssl_certificate_key "/etc/pki/nginx/private/server.key";
ssl_ciphers PROFILE=SYSTEM;
```

And add the following line.
```
ssl_protocols TLSv1.2;
```

- Add the following as a new block below the second block.
```
# Set this to the stanza path configured in /etc/nitro_enclaves/acm.yaml
include "/etc/pki/nginx/nginx-acm.conf";
```
The completed section should appear as follows.
```
# Settings for a TLS enabled server.
#
    server {
        listen       443 ssl http2;
        listen       [::]:443 ssl http2;
        server_name  example.com;
        root         /usr/share/nginx/html;
        
        ssl_protocols TLSv1.2;
        ssl_session_cache shared:SSL:1m;
        ssl_session_timeout  10m;
        ssl_prefer_server_ciphers on;
        
        # Set this to the stanza path configured in /etc/nitro_enclaves/acm.yaml
        include "/etc/pki/nginx/nginx-acm.conf";
        
        # Load configuration files for the default server block.
        include /etc/nginx/default.d/*.conf;
        
        error_page 404 /404.html;
            location = /40x.html {
        }
        error_page 500 502 503 504 /50x.html;
            location = /50x.html {
        }
    }
```

6. Start the ACM for Nitro Enclaves service and ensure that it starts automatically at instance boot.
```
$ sudo systemctl start nitro-enclaves-acm.service
$ sudo systemctl enable nitro-enclaves-acm
```

7. Test that the ACM for Nitro Enclaves is working as expected.

If you used a public certificate, use the following command.
```
$ curl https://host_name_or_IP
```



#### reference 

[register a new domain](https://docs.aws.amazon.com/Route53/latest/DeveloperGuide/domain-register.html)

[request a public certificate](https://docs.aws.amazon.com/acm/latest/userguide/gs-acm-request-public.html)


#### misc
- notice the inbound rules of the parent instance(ssh port 22 & tcp port 443 need to be open)
