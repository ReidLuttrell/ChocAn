# ChocAn
A medical record user and provider interface. Implements functionality for Users, Managers, Providers and Operators to create members, provide services, store members, services, and billing information.

To build, type "make", this produces an executable named "ChocAn", which is executed with "./ChocAn".
To clean, type "make clean", this removes the object files and the executable.
The different users of the system are derived classes from the "User" base.
each derived class has a virtual "Flow" method that defines the specific functionality
that is specific to that type of user.
