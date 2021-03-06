Contextual Reliance on Sequences/Services (Cross)
=================================================

The challenge of most large software systems is-

* Booting systems in a complex order and respecting their dependencies
* Allowing access across "modules" without the use of singletons or parameter chaining that introduces dependencies
* Supporting decoupled plugin-like features that can contain their own code in a binary or framework
* When errors occur in a system flow, elegantly support unique flows to recover/exit

Sequencing Order
----------------

A sequence of modules means running modules in a specified order, and using minimal coordination between the modules to transition.  The sequence can be declared static or dynamic.  The flow of a sequence can include directional transitions, and decision-making at runtime (called "junctions") to select a branching flow.  Various sequences can be chained together to describe complex series of functionalities.

System Services
---------------

A given flow's module can use its location in the system to request a registered service that can provide functionality or utility.

TODOs
-------
* Write more unit tests
* Add more documentation
* make allocator actually come from specified pools of memory (use boost fast pool for context/seqnode)
* make sure context/services can be customized per module/sequence/junction
* analyze performance
* investigate running lib in web server and connecting from website
* consistently use boost or std ( abstracted away as much as possible )
