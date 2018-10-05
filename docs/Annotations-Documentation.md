Annotations documentation
=========================


Annotations are used to generate additional functions and structs. They stand before an attribute in a struct or before a struct definition in the comments. None annotation can be used before both. Following annotations are currently available. For examples, please refer to the Imps Engine source code. Multi-dimensional arrays are not supported:



1. General annotations:
- @extend: This will include all functions from the attributes class and will map them to the class itself. Functions generated using annotations will also be mapped. With this behaviour an inheritance-like oop-mechanism can be achieved. Must only be used with the first attribute of the struct. Cannot be used with pointers and arrays (function pointers included).


2. Setter annotations:
- @set: This generates a setter function. The attribute type will be used as an argument for the function.
- @setAsRef: This also generates a setter function, but as an argument a reference to the attribute will be used as an argument for the function. Cannot be used with function pointers.
- @setAsCharArray: Can only be used with attributes of type “IAString” or “IAString *”. Creates a function with “const char *” as an argument. This char array will be used to set the string to its value.
-> Setter annotations cannot be used with arrays.


3. Getter annotations:
- @get: This generates a getter function. The attribute will be returned with its type. Cannot be used with arrays. For arrays use @getAsRef instead.
- @getAsConst: This works like @get, but the “const” qualifier will be added before the type of the returned attribute. Makes only sense at using with pointers.
- @getAsRef: This generates a getter function, that creates a reference of the attribute and returns it. C
- @getAsConstRef: This works like @getAsRef, but the “const” qualifier will be added before the type of the returned attribute. Must be used in contrast to “@getAsRef” with non-pointer attributes (Arrays are allowed, pointers to arrays are not). The advantage of using “@getAsConstRef” over “getAsRef” is, that you can use it with a constant struct reference.
- @getAsCharArray: Can only be used with attributes of type “IAString” or “IAString *”. Creates a function which will convert the attribute into a char array with type “const char *” and returns it.


4. Annotations only applicable to function pointers:
- @respondsTo: This creates a function which will return a boolean variable either true or false if the function pointer is set or not, respectively.
- @exe: This will create a function, which will dereference the function pointer and call it using an object reference from the struct itself and passing the attributes through. The name from the function pointer’s first parameter argument will be used to get the object reference from the struct. The 2nd and following parameter arguments of the function pointer will get directly passed through.


5. Annotations only applicable to locks (“IALock”, “IALock *”, “IARecursiveLock”, “IARecursiveLock *”):
- @lock: Generates a lock and an unlock function for the corresponding lock.


6. Annotations for events:
- @event: This can only be used before a struct definition, ideally a delegate. It will create a new class using the same classname, trying to remove a “Delegate” suffix and and adding an “Event” suffix. The new class will implement basic event functionality, concretely it will provide functions for register- and unregistering delegates and calling function-pointers from all registered delegates that are marked with the annotation “@exe” and has the return type “void”.
- @register: This annotation is only applicable to an attribute which is an event. Generates a register and an unregister function for the corresponding event.