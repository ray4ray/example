#! /bin/bash

regis="$1"
tag="$2"


echo "################# delete current mcu & test images ##############################"
currentMcuImage=$(sudo docker images | grep 'ccs-mcu ' | awk  -F ' ' '{print $3}')
echo "current mcu image:"
echo $currentMcuImage
if [ -z "$currentMcuImage" ]; then
    echo "no mcu image, don't delete"
else
    sudo docker rmi $currentMcuImage
fi

currentMcuTestImage=$(sudo docker images | grep 'ccs-mcu-test ' | awk  -F ' ' '{print $3}')
echo "current mcu test image:"
echo $currentMcuTestImage
if [ -z "$currentMcuTestImage" ]; then
    echo "no mcu image, don't delete"
else
    sudo docker rmi $currentMcuTestImage
fi

echo "#################### pull and push mcu & test images ################################"

if [[ "$regis" = offical* ]]; then
    sudo docker pull rcp-docker-containers-local.esisoj70.emea.nsn-net.net/ccs-mcu/ccs-mcu:$tag
else
    sudo docker pull rcp-docker-testing-local.esisoj70.emea.nsn-net.net/ccs-mcu/ccs-mcu:$tag
fi
newMcuImage=$(sudo docker images | grep 'ccs-mcu ' | awk  -F ' ' '{print $3}')
sudo docker tag $newMcuImage  registry.kube-system.svc.nokia.net:5555/ccs-mcu/ccs-mcu:$tag
sudo docker push registry.kube-system.svc.nokia.net:5555/ccs-mcu/ccs-mcu:$tag

echo "deregister mcu image from docker registery"
if [[ "$regis" = offical* ]]; then
    sudo docker rmi rcp-docker-containers-local.esisoj70.emea.nsn-net.net/ccs-mcu/ccs-mcu:$tag
else
    sudo docker rmi rcp-docker-testing-local.esisoj70.emea.nsn-net.net/ccs-mcu/ccs-mcu:$tag
fi

sudo docker pull rcp-docker-testing-local.esisoj70.emea.nsn-net.net/ccs-mcu/ccs-mcu-test:$tag
newMcuTestImage=$(sudo docker images | grep 'ccs-mcu-test ' | awk  -F ' ' '{print $3}')
sudo docker tag $newMcuTestImage registry.kube-system.svc.nokia.net:5555/ccs-mcu/ccs-mcu-test:$tag
sudo docker push registry.kube-system.svc.nokia.net:5555/ccs-mcu/ccs-mcu-test:$tag

echo "deregister mcu test image from docker registery"
sudo docker rmi rcp-docker-testing-local.esisoj70.emea.nsn-net.net/ccs-mcu/ccs-mcu-test:$tag
