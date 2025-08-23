# get_started_with_CAN_on_Ubuntu

## Prep

Before you start with this tutorial, make sure you have a USB to CAN Adapter. For this tutorial, I used RHO2.

## Enabling CAN

Open your terminal and run: 

```bash
sudo modprobe can
sudo modprobe can_raw
sudo apt-get install can-utils
```

And if your run:


```bash
ip a
```
Your output should be something like:

```bash
jinm@Aspire :~$ ip a
... ...
9: can0: <NOARP ,ECHO > mtu 16 qdisc noop state DOWN group default qlen 10
link/can
```
