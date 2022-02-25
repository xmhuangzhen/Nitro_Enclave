# 03 Persistence

[s3 user guide](https://docs.aws.amazon.com/AmazonS3/latest/userguide/Welcome.html)

[s3 get started](https://docs.aws.amazon.com/AmazonS3/latest/userguide/GetStartedWithS3.html)

[KMS API reference](https://docs.aws.amazon.com/kms/latest/APIReference/Welcome.html)

### s3 startup

[get started](https://docs.aws.amazon.com/AmazonS3/latest/userguide/GetStartedWithS3.html)

[s3 prerequisite](https://docs.aws.amazon.com/AmazonS3/latest/userguide/setting-up-s3.html)

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

[]



