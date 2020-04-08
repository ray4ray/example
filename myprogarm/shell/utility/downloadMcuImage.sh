#! /bin/bash

regis="$1"
tag="$2"
xptag="$3"


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
    MCUImage=rcp-docker-containers-local.esisoj70.emea.nsn-net.net/ccs-mcu/ccs-mcu:$tag
else
    MCUImage=rcp-docker-testing-local.artifactory-espoo2.int.net.nokia.com/ccs-mcu/ccs-mcu:$tag
fi
sudo docker pull $MCUImage
sudo docker tag $MCUImage registry.kube-system.svc.nokia.net:5555/ccs-mcu/ccs-mcu:$tag
sudo docker push registry.kube-system.svc.nokia.net:5555/ccs-mcu/ccs-mcu:$tag

echo "deregister mcu image from docker registery"
sudo docker rmi $MCUImage
sudo docker images | grep 'ccs-mcu '


if [[ "$regis" = offical* ]]; then
    XPIFImage=rcp-docker-containers-local.esisoj70.emea.nsn-net.net/xpif/xpif:$xptag
else
    XPIFImage=rcp-docker-testing-local.artifactory-espoo2.int.net.nokia.com/xpif/xpif:$xptag
fi
sudo docker pull $XPIFImage
sudo docker tag $XPIFImage registry.kube-system.svc.nokia.net:5555/xpif/xpif:$xptag
sudo docker push registry.kube-system.svc.nokia.net:5555/xpif/xpif:$xptag

echo "deregister mcu image from docker registery"
sudo docker rmi $XPIFImage
sudo docker images | grep 'xpif '


if [[ "$regis" = offical* ]]; then
    echo "for offical image, do nothing for test image"
else
    MCUTESTImage=rcp-docker-testing-local./rtifactory-espoo2.int.net.nokia.com/ccs-mcu/ccs-mcu-test:$tag
    sudo docker pull $MCUTESTImage
    sudo docker tag $MCUTESTImage registry.kube-system.svc.nokia.net:5555/ccs-mcu/ccs-mcu-test:$tag
    sudo docker push registry.kube-system.svc.nokia.net:5555/ccs-mcu/ccs-mcu-test:$tag

    echo "deregister mcu test image from docker registery"
    sudo docker rmi $MCUTESTImage
fi


currentLWSDImage=$(sudo docker images | grep 'docker-lwsd ' | awk  -F ' ' '{print $3}')
if [ -z "$currentLWSDImage" ]; then
    echo "######### current no lwsd image in local, download lwsd image ####################"
    LWSDImage=rcp-docker-containers-local.esisoj70.emea.nsn-net.net/lwsd/docker-lwsd:1.0.1
    sudo docker pull $LWSDImage
    sudo docker tag $LWSDImage registry.kube-system.svc.nokia.net:5555/lwsd/docker-lwsd:1.0.1
    sudo docker rmi $LWSDImage
fi
