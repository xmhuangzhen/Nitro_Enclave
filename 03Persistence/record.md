# 03 Persistence

### sketch

(1) create a "KMS" key in nitro enclave (see part [05KMS](/05KMS/record.md) for more details.)
(2) encrypt the objects in the enclave using the KMS key
(3) transmit the objects to the parent instance 
(4) parent instance upload it to s3.



#### s3 startup

1. sign in as a root use
2. [Add an user](https://console.aws.amazon.com/iamv2/home?#/users) in IAM role
3. Select the check box next to AWS Management Console access. Then select Custom password, and then enter your new password in the text box.
4. (Optional) By default, AWS requires the new user to create a new password when first signing in. You can clear the check box next to User must create a new password at next sign-in to allow the new user to reset their password after they sign in.
5. Choose Next: Permissions.
6. Under Set permissions, choose Add user to group.
7. Choose Create group.
8. Choose Filter policies, and then select AWS managed - job function to filter the table contents.
9. In the policy list, select the check box for AdministratorAccess. Then choose Create group.
10. Back in the list of groups, select the check box for your new group. Choose Refresh if necessary to see the group in the list.
11. Choose Next: Tags.
12. (Optional) Add metadata to the user by attaching tags as key-value pairs. For more information about using tags in IAM, see Tagging IAM entities in the IAM User Guide.
13. sign in as an IAM user

[s3 step1 create s3 bucket](https://docs.aws.amazon.com/AmazonS3/latest/userguide/creating-bucket.html)

#### the status after uploading and downloading files

|file type|status|
|--|--|
|.c / .cpp | to .txt |
|.html/.java/.py/.js/.go/.php|origin|

####

1. launch an ec2 instance which contains the IAM role containing "AmazonS3FullAccess" permissions policy
2. upload something to the s3 bucket "TheBucketName" by `aws s3 cp ./FileName s3://TheBucketName`
3. After modifying the file, you can sync the file by `aws s3 sync . s3://TheBucketName`



### references

[s3 get started](https://docs.aws.amazon.com/AmazonS3/latest/userguide/GetStartedWithS3.html)

[chinese tutorial](https://aws.amazon.com/cn/s3/)

[s3 prerequisite](https://docs.aws.amazon.com/AmazonS3/latest/userguide/setting-up-s3.html)

[s3 user guide](https://docs.aws.amazon.com/AmazonS3/latest/userguide/Welcome.html)

[KMS API reference](https://docs.aws.amazon.com/kms/latest/APIReference/Welcome.html)



[kms link](https://aws.amazon.com/kms/)

[kms overview](https://docs.aws.amazon.com/kms/latest/developerguide/overview.html)


[How Amazon Simple Storage Service (Amazon S3) uses AWS KMS](https://docs.aws.amazon.com/kms/latest/developerguide/services-s3.html)

[connect S3 from an EC2 instance](https://www.youtube.com/watch?v=YYtvL459uWY)
[s3 command intro](https://awscli.amazonaws.com/v2/documentation/api/latest/reference/s3/index.html)
[s3 commands with cli](https://docs.amazonaws.cn/en_us/cli/latest/userguide/cli-services-s3-commands.html)

[server-side encryption - kms](https://docs.aws.amazon.com/AmazonS3/latest/userguide/UsingKMSEncryption.html)


[nitro](https://github.com/MarkBiesheuvel/demo-templates/tree/master/nitro-enclaves)


