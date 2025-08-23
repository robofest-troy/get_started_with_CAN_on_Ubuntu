# include <iostream> // For console output (e.g., "Hello World !")
# include <unistd.h> // For close ()
# include <net/if.h> // For if_nametoindex ()
# include <sys/socket.h> // For socket (), bind (), sendto ()
# include <linux/can.h> // For CAN_RAW , struct can_frame
# include <linux/can/raw.h> // For CAN_RAW_FD_FRAMES
# include <cstring> // For memset ()
# include <sys/ioctl.h> // Correct header for the ioctl () function

int main () {
  int s;
  struct sockaddr_can addr;
  struct can_frame frame;
  struct ifreq ifr;

  // 1. Create a CAN socket
  s = socket (PF_CAN , SOCK_RAW , CAN_RAW );
  if (s < 0) {
    perror ("Error creating socket ");
    return 1;
  }
  
  // 2. Specify the CAN interface (e.g., "can0 ")
  strcpy (ifr.ifr_name , "can0"); // Replace "can0" with your CAN interface name
  ioctl(s, SIOCGIFINDEX , &ifr);

  addr. can_family = AF_CAN ;
  addr. can_ifindex = ifr. ifr_ifindex ;
  
  // 3. Bind the socket to the CAN interface
  if (bind(s, (struct sockaddr *)&addr , sizeof (addr)) < 0) {
    perror ("Error binding socket ");
    close(s);
    return 1;
  }
  
  // 4. Prepare the CAN frame
  frame.can_id = 0x123; // Example CAN ID
  frame. can_dlc = 8; // Data Length Code (number of data bytes)
  strcpy (( char *) frame.data , "Hello!"); // "Hello !" as data
  
  // 5. Send the CAN frame
  if (write(s, &frame , sizeof (struct can_frame )) < 0) {
    perror ("Error sending CAN frame");
    close(s);
    return 1;
  }
  
  std :: cout << "CAN 'Hello World!' frame sent successfully on can0." << std :: endl;
  
  // Close the socket
  close(s);
  return 0;
}
  
