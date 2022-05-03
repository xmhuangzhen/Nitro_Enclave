# 05 KMS


### prerequisite

1. create an aws account(IAM user) with `administrator access` policy.

2. create a cloud9 environment

(a) Download the AWS CloudFormation template from this workshop’s GitHub repo.
```
curl https://raw.githubusercontent.com/aws-samples/aws-nitro-enclaves-workshop/main/resources/templates/cloud9.yaml -o cloud9.yaml
```

(b) Navigate to the AWS CloudFormation console to create a new stack. https://console.aws.amazon.com/cloudformation/home#/stacks/create/template

(c) Select and upload the CloudFormation template that was downloaded previously. Then click Next.
 
(d) Name your stack `NitroEnclavesWorkshop` and, if you’d like, increase the volume size beyond the default value. Then click Next.

(e) Leave the stack options as-is and proceed to the next step by clicking Next.

(f) Select all three capabilities and click Create stack.

(h) This is an excellent time to stretch your legs while the stack is created and reaches  `CREATE_COMPLETE`. This takes about 5 minutes.

(i) Navigate to the AWS Cloud9 console to view and open your environment IDE.

https://console.aws.amazon.com/cloud9/home

(j) Open your Cloud9 environment IDE in a new tab.

3. Disable AWS managed temporary credentials in cloud9

(a) With your AWS Cloud9 environment open, in the AWS Cloud9 IDE, on the menu bar, choose the **AWS Cloud9 icon, Preferences**.

(b) On the **Preferences** tab, in the navigation pane, scroll to end and choose **AWS Settings, Credentials**.

(c) Toggle **AWS managed temporary credentials** off to turn AWS managed temporary credentials off.

4. Install and configure Nitro Enclaves CLI and tools

(a) Install the Nitro Enclaves CLI, which will enable you to run enclaves.
```
$ sudo amazon-linux-extras install aws-nitro-enclaves-cli -y
```
(b) Install the Nitro Enclaves development tools. This will enable you to build enclaves.
```
$ sudo yum install aws-nitro-enclaves-cli-devel -y
```
(c) Configure user permissions.
```
$ sudo usermod -aG ne $USER
$ sudo usermod -aG docker $USER
```
(d) Verify that the Nitro Enclaves CLI was installed correctly.
```
$ nitro-cli --version
```
The output should look similar to
```
Nitro CLI <VERSION>
```

(e)modify pre-allocated memory in `/etc/nitro_enclaves/allocator.yaml` to 4000MB


(f) Start and enable the Nitro Enclaves allocator service.
```
$ sudo systemctl start nitro-enclaves-allocator.service && sudo systemctl enable nitro-enclaves-allocator.service
```
(g) Start and enable the Docker service.
```
$ sudo systemctl start docker && sudo systemctl enable docker
```
(h) Reboot the instance. At this point, we would need to log out and log back in to ensure that the `usermod` command that appended user to groups takes effect. One option could be to start a new shell with something like `exec sudo su --login $USER`, and another could be by preparing the `groupadd` and `usermod` commands before the current shell login. However, since Cloud9 handles reboots gracefully and returns the shell to a similar state, we’ll restart the instance.
```
$ sudo shutdown -r now
```
This takes a moment (about 30 seconds) to complete.

(i) Verify that `ec2-user` is a member of both the `docker` and `ne` groups.
```
$ id $USER
```
The output should look similar to
```
uid=1000(ec2-user) gid=1000(ec2-user) groups=1000(ec2-user),4(adm),10(wheel),190(systemd-journal),991(docker),1001(ne)
```

5. Clone the repository

Use `git clone` to download a copy of this workshop’s repository. This repo includes the content used in subsequent modules.
```
$ git clone https://github.com/xmhuangzhen/Nitro_Enclave.git
```

6. Compile the dependencies for the Nitro Enclaves Workshop base image

Nitro Enclaves use docker images as a convenient format for packaging the applications you wish to launch in an enclave. Some of the sample applications in this workshop require dependencies that must be compiled.

To package these dependencies as a base docker image:

(a) Start a new terminal session. (To start a new terminal session, on the menu bar, choose **Window, New Terminal**.)

(b) Change directory to the code directory for the My First Enclave module by entering the following command:
```
$ cd ~/environment/Nitro_Enclave/05KMS/getting-started
```
(c) Initiate the image build process by entering the following command:
```
$ docker build ./ -t "enclave_base"
```


### cryptographic attestation

1. Create a KMS CMK using the AWS Management Console

(a) Sign in to the AWS Management Console and open the AWS Key Management Service (AWS KMS) console at https://console.aws.amazon.com/kms.

(b) To change the AWS Region, use the Region selector in the upper-right corner of the page.

(c) In the navigation pane, choose **Customer managed keys**.

(d) Choose **Create key**.

(e) For **Key type** select **Symmetric**.

(f) Choose **Next**.

(g) Type the alias `my-enclave-key` for the CMK.

(h) Choose **Next**.

(i) Do not select any IAM users or roles that can administer the CMK.

(j) Choose **Next**.

(k) Do not select any IAM users or roles that can use the CMK for cryptographic operations

(l) Choose **Next**.

(m) Review the key settings that you chose. You can still go back and change all settings.

(n) Choose **Finish** to create the CMK.


2. Configure your KMS key policy

Your KMS key policy should now contain a single statement that allows IAM users and roles to be granted access to the key via their IAM policy documents. This statement should look similar to

```
    "Statement": [
        {
            "Sid": "Enable IAM User Permissions",
            "Effect": "Allow",
            "Principal": {
                "AWS": "arn:aws:iam::111122223333:root"
            },
            "Action": "kms:*",
            "Resource": "*"
        }
    ]
```

The IAM principal associated with your Cloud9 Environment is not granted permission in its IAM policies to perform any actions on your CMK. For example, if you attempt to view metadata about the key from your Cloud9 terminal by issuing the following command you will be denied:

```
$ aws kms describe-key --key-id "alias/my-enclave-key"
```

In order to enable your Cloud9 environment to use the key to encrypt and decrypt data, you’ll configure that permission in the KMS Key Policy directly.

To prepare a new key policy for your CMK:

(a) Store the AWS IAM principal and account associated with your Cloud9 environment in an environment variable by executing the following command in your Cloud9 terminal:

```
$ export AWS_PRINCIPAL=`aws sts get-caller-identity | jq -r ".Arn"`
$ export ACCOUNT_ID=`aws sts get-caller-identity | jq -r ".Account"`
```
(b) Customize a pre-prepared key policy template with these values by executing the following command in your Cloud9 terminal.

```
$ cd ~/environment/aws-nitro-enclaves-workshop/resources/code/my-first-enclave/cryptographic-attestation
$ sed -e "s|ACCOUNT_ID|${ACCOUNT_ID}|" -e "s|AWS_PRINCIPAL|${AWS_PRINCIPAL}|" key_policy_template.json > key_policy.json
```

3. Update the key policy for your CMK:

(a) Open the AWS Key Management Service (AWS KMS) console at https://console.aws.amazon.com/kms.

(b) To change the AWS Region, use the Region selector in the upper-right corner of the page.

(c) To view the keys in your account that you create and manage, choose **Customer managed keys** in the navigation pane.

(d) In the list of CMKs, choose the alias **my-enclave-key**.

(e) Choose the **Key policy** tab.

(f) On the **Key policy** tab, you will see the default view. To see the key policy document, choose **Switch to policy view**. You will see the key policy document. This is policy view. In the key policy statements, you can see the principals who have been given access to the CMK by the key policy, and you can see the actions they can perform.

(g) In another window, return to your Cloud9 terminal and issue the `ls` command and choose **key_policy.json** with your cursor.

(h) Select **Open**.

(i) Your new key policy will open in a Cloud9 editor tab. Please select all the text in the window and copy it to your system clipboard.

(j) Return to your window with your KMS CMK **Key policy** tab open. Select **Edit**.

(k) Delete the entire key policy and paste your new key policy in its place and then choose **Save changes**.


4. Build, run, and connect to your enclave in debug mode





### references

[KMS API reference](https://docs.aws.amazon.com/kms/latest/APIReference/Welcome.html)



[kms link](https://aws.amazon.com/kms/)

[kms overview](https://docs.aws.amazon.com/kms/latest/developerguide/overview.html)
[server-side encryption - kms](https://docs.aws.amazon.com/AmazonS3/latest/userguide/UsingKMSEncryption.html)


[KMS nitro enclave sample](https://github.com/aws-samples/aws-nitro-enclaves-workshop)

[crypto attestation tutorial](https://nitro-enclaves.workshop.aws/en/my-first-enclave/cryptographic-attestation.html)
