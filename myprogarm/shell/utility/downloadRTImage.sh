#! /bin/bash

regis="$1"
tag="$2"
nitag="$3"
nmtag="$4"

currentDpmImage=$(sudo docker images | grep 'ccs-rt-dpm ' | awk  -F ' ' '{print $3}')
echo "current ccs-rt-dpm image:"
echo $currentDpmImage
if [ -z "$currentDpmImage" ]; then
    echo "no mcu image, don't delete"
else
    sudo docker rmi $currentDpmImage
fi

currentDpmTrsImage=$(sudo docker images | grep 'ccs-rt-dpm-trs '  | awk  -F ' ' '{print $3}')
echo "current ccs-rt-dpm-trs  image:"
echo $currentDpmTrsImage
if [ -z "$currentDpmTrsImage=" ]; then
    echo "no dpm trs, don't delete"
else
    sudo docker rmi $currentDpmTrsImage
fi

currentemodpImage=$(sudo docker images | grep 'ccs-rt-emodp '  | awk  -F ' ' '{print $3}')
echo "current ccs-rt-emodp image:"
echo $currentemodpImage
if [ -z "$currentemodpImage" ]; then
    echo "no emodp image, don't delete"
else
    sudo docker rmi $currentemodpImage
fi


sudo docker pull rcp-docker-containers-local.esisoj70.emea.nsn-net.net/nwinit/docker-nwinit:$nitag
sudo docker tag rcp-docker-containers-local.esisoj70.emea.nsn-net.net/nwinit/docker-nwinit:$nitag  registry.kube-system.svc.nokia.net:5555/nwinit/docker-nwinit:$nitag
sudo docker push registry.kube-system.svc.nokia.net:5555/nwinit/docker-nwinit:$nitag
echo "delete dpm image from docker registery"
sudo docker rmi rcp-docker-containers-local.esisoj70.emea.nsn-net.net/nwinit/docker-nwinit:$nitag


sudo docker pull rcp-docker-containers-local.esisoj70.emea.nsn-net.net/nwmgmt/docker-nwmgmt:$nmtag
sudo docker tag rcp-docker-containers-local.esisoj70.emea.nsn-net.net/nwmgmt/docker-nwmgmt:$nmtag  registry.kube-system.svc.nokia.net:5555/nwmgmt/docker-nwmgmt:$nmtag
sudo docker push registry.kube-system.svc.nokia.net:5555/nwmgmt/docker-nwmgmt:$nmtag
echo "delete dpm image from docker registery"
sudo docker rmi rcp-docker-containers-local.esisoj70.emea.nsn-net.net/nwmgmt/docker-nwmgmt:$nmtag


if [[ "$regis" = offical* ]]; then
    sudo docker pull rcp-docker-containers-local.esisoj70.emea.nsn-net.net/ccs-rt/ccs-rt-dpm:$tag
else
    sudo docker pull rcp-docker-testing-local.esisoj70.emea.nsn-net.net/ccs-rt/ccs-rt-dpm:$tag
fi
newMcuImage=$(sudo docker images | grep 'ccs-rt-dpm ' | awk  -F ' ' '{print $3}')
sudo docker tag $newMcuImage  registry.kube-system.svc.nokia.net:5555/ccs-rt/ccs-rt-dpm:$tag
sudo docker push registry.kube-system.svc.nokia.net:5555/ccs-rt/ccs-rt-dpm:$tag
echo "delete dpm image from docker registery"
if [[ "$regis" = offical* ]]; then
    sudo docker rmi rcp-docker-containers-local.esisoj70.emea.nsn-net.net/ccs-rt/ccs-rt-dpm:$tag
else
    sudo docker rmi rcp-docker-testing-local.esisoj70.emea.nsn-net.net/ccs-rt/ccs-rt-dpm:$tag
fi


if [[ "$regis" = offical* ]]; then
    sudo docker pull rcp-docker-containers-local.esisoj70.emea.nsn-net.net/ccs-rt/ccs-rt-dpm-trs:$tag
else
    sudo docker pull rcp-docker-testing-local.esisoj70.emea.nsn-net.net/ccs-rt/ccs-rt-dpm-trs:$tag
fi
newMcuImage=$(sudo docker images | grep 'ccs-rt-dpm-trs ' | awk  -F ' ' '{print $3}')
sudo docker tag $newMcuImage  registry.kube-system.svc.nokia.net:5555/ccs-rt/ccs-rt-dpm-trs:$tag
sudo docker push registry.kube-system.svc.nokia.net:5555/ccs-rt/ccs-rt-dpm-trs:$tag
echo "delete dpm-trs image from docker registery"
if [[ "$regis" = offical* ]]; then
    sudo docker rmi rcp-docker-containers-local.esisoj70.emea.nsn-net.net/ccs-rt/ccs-rt-dpm-trs:$tag
else
    sudo docker rmi rcp-docker-testing-local.esisoj70.emea.nsn-net.net/ccs-rt/ccs-rt-dpm-trs:$tag
fi


if [[ "$regis" = offical* ]]; then
    sudo docker pull rcp-docker-containers-local.esisoj70.emea.nsn-net.net/ccs-rt/ccs-rt-emodp:$tag
else
    sudo docker pull rcp-docker-testing-local.esisoj70.emea.nsn-net.net/ccs-rt/ccs-rt-emodp:$tag
fi
newMcuImage=$(sudo docker images | grep 'ccs-rt-emodp ' | awk  -F ' ' '{print $3}')
sudo docker tag $newMcuImage  registry.kube-system.svc.nokia.net:5555/ccs-rt/ccs-rt-emodp:$tag
sudo docker push registry.kube-system.svc.nokia.net:5555/ccs-rt/ccs-rt-emodp:$tag
echo "delete emodp image from docker registery"
if [[ "$regis" = offical* ]]; then
   sudo docker rmi rcp-docker-containers-local.esisoj70.emea.nsn-net.net/ccs-rt/ccs-rt-emodp:$tag
else
   sudo docker rmi rcp-docker-testing-local.esisoj70.emea.nsn-net.net/ccs-rt/ccs-rt-emodp:$tag
fi

