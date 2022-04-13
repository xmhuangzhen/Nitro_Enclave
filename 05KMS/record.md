# 05 KMS
[tutorial](https://github.com/aws-samples/aws-nitro-enclaves-workshop)
#### prerequisite
```
aws configure

sudo yum update -y
sudo amazon-linux-extras install aws-nitro-enclaves-cli -y
sudo yum install aws-nitro-enclaves-cli-devel python3 python git -y
sudo usermod -aG ne $USER
sudo usermod -aG docker $USER

```

modify pre-allocated memory in `/etc/nitro_enclaves/allocator.yaml` to 4000MB

```
sudo systemctl start nitro-enclaves-allocator.service && sudo systemctl enable nitro-enclaves-allocator.service
sudo systemctl start docker && sudo systemctl enable docker
```

reboot the instance


#### 
````
git clone https://github.com/xmhuangzhen/Nitro-Enclave-KMS.git

cd Nitro-Enclave-KMS


git clone https://github.com/aws-samples/aws-nitro-enclaves-workshop.git
cd aws-nitro-enclaves-workshop/resources/code/getting-started
docker build ./ -t "enclave_base"

docker build ./ -t "data-processing"
nitro-cli build-enclave --docker-uri "data-processing:latest" --output-file "data-processing.eif"
nitro-cli run-enclave --debug-mode --cpu-count 2 --memory 2500 --eif-path "./data-processing.eif" 
ENCLAVE_ID=$(nitro-cli describe-enclaves | jq -r ".[0].EnclaveID")
[ "$ENCLAVE_ID" != "null" ] && nitro-cli console --enclave-id ${ENCLAVE_ID}
````

```

cd Nitro-Enclave-KMS
pip3 install --user -r "requirements.txt"
python3 client.py --prepare --values "values.txt"  --alias "my-enclave-key"
python3 client.py --submit --ciphertext "string.encrypted"  --alias "my-enclave-key"
```

python3 client.py --prepare --values "values.txt"  --alias "KMStest2"
python3 client.py --submit --ciphertext "string.encrypted"  --alias "KMStest2"
