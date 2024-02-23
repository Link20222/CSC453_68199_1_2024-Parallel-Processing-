Classification of Architectures:
Single Instruction Single Data   (SISD)
Single Instruction Multiple Data (SIMD)
Multiple Instruction Single Data (MISD)
Multiple Instruction Multiple Data (MIMD)

SIMD:
single instruction stream is broadcasted to multiple
processors Each having its own data stream
((Instruction)كل بروسيس عنده داتا سيت مختلف بس نفس  الانستركشن)
مثال: ابغى اجيب الافرج على كل الشعب

MISD:
عندي ملتبل الانستركشن على نفس الداتا سيت
مثال :ابغى اجيب الافرج والقريد على نفس الشعبه

MIMD:
عندي ملتبل الانستركشن وملتبل الداتاسيت

Shared Memory Paradigm:
Shared memory
Distributed memory
Hybrid systems

Shared Memory:
لو خرب الميموري يخرب كل النظام

Distributed memory:
لو خرب الميموري ما يخرب كل شيء

Hybrid Shared Memory:
overload اقل

Message Passing Paradigm:

Allows for communication between a set of
processors.

Each processor is required to have a local
memory, no global memory is required.

Communication occurs between processors by
sending and receiving messages.
--------------------------------------------------------------------------------
BASIC OP:
1)Blocking non-buffered send/ receive:(يرسل رساله ويوقف شغل اللين ما يجيه ريسيف)
  the sender issues a send operation and cannot proceed
  until a matching receive at the receiver’s side is
  encountered and the operation is complete

2)Blocking buffered send/ receive:  (هنا ما راح يكون فيه وقت انتظار طويل لانه الانتظار اللي راح يكون بيكون انه يوصل الرساله للبفر موب للرسيف زي اللي فوق + في العاده يكون البافر في الريسيفر سايد + الريسيفر راح يقرا الداتا من البفر )
  when the sender process reaches a send operation it
  copies the data into the buffer on its side and can proceed
  without waiting.

  At the receiver side it is not necessary that the received
  data will be stored directly at the designated location.

  When the receiver process encounters a receive
  operations it checks the buffer for data.

3)Non-Blocking non-buffered send/ receive:( هنا اللي راح يصير السيندير راح يكمل شغله اللين الريسيفر  يكون جاهز بعدين بيرسله انتربت  ويوقف شغله بعدين يرسل المسج وبعدها يكمل )
  the process needs not to be idle but instead can do useful
  computations while waiting for the send / receive
  operation to complete.

  4)Non-Blocking buffered send/ receive:(هنا السيندر راح يحط الداتا في الميموري بس بيسوي ثريد يخلي يحط الداتا وبعدين يجي الريسيفر يسوي ثريد ياخذ الداتا من الميوري  وهذي الطريقه هي الباريل)
  he sender issues a direct memory access operation
  (DMA) to the buffer. DMA operations can be carried out
  without processor being involved.

  The sender can proceed with its computations.
  At the receiver side, when a receive operation is
  encountered the data is transferred from the buffer to
  memory location.


  Broadcast:(نرسل نفس الداتا لكل الشايلد)
  This function allows one process (called the root) to send
  the same data to all communicator members.

  Scatter:(نرسل الداتا لشايلد بس يقسم الداتا)
  Alows one process to give out the content of its send
  buffer to all processes in a communicator.

  Gather:(هنا تجمع الداتا  وتحطهم عند البارينت)
  Each process gives out the data in its send buffer to the
  root process which stores them according to their ranks.
--------------------------------------------------------------------------------
MULTI-THREADING Paradigm:

1) In a single-core (superscalar) system:(عندنا كيو حلو فيه ثريدز وعندنا بروسيسر البروسيسر ياخذ الهيد حق الكيو وبعدين يصير الثريد شغال على البروسيسر بعدين يرجعه للكيو )
  we can define multithreading as the ability of the
  processor’s hardware to run two or more threads in an
  overlapping fashion by allowing them to share the
  functional units of that processor.

2) in a multi-core system:(نفس الطريقه بس انه يصير في اكثر من بروسيسر بحيث  انه كل ثريد ياخذ بروسيسر)
  we can define multithreading as the ability of two or more
  processors to run two or more threads simultaneously (in
  parallel) where each thread run on a separate processo

3)  Modern systems combine both multithreading
    approaches(يصير كل بروسيس عنده كيو خاص فيه ونفسم الثريدز الى مجموعات).
--------------------------------------------------------------------------------
Parallel Programming Models:
- Single Program Multiple Data (SPMD)
- Task Farming
- Divide and Conquer
- Dataflow
--------------------------------------------------------------------------------
Single Program Multiple Data (SPMD):(في العاده في البروسيسر يقسم الداتا على نودز مختلفه  بعدين النود يسوي بعض الحسابات ويشارك الداتا المهمه بعدين يجمعهم)
A single program is loaded into each node of a
parallel system

Node are executing the code independently but
act on multiple data sets including "private" and
" shared " data.

Program components:
1. Source code
2. Load Balancing Strategy
3. Skeleton
--------------------------------------------------------------------------------
Task Farming Model:
Task farming (or Master-Worker or Master-Slave
  or Manager-Worker) consists of two entities:
      -the master
      -and many workers.
The master: هو اللي يقسم المشكله ويوزعه على الوركر بعدين يجمع النتائج
  decomposes the problem into small tasks,

  then distributes/farms these tasks among a farm of
  workers

  and finally collects the partial results to produce the final
  result of the computation.

The worker: يستقبل المهمه  ويشتغل عليها بعدين يرجع النتائج للماستر ما يتواصلون مع بعض
  receives a task, process it and send the result back to
  the master.
--------------------------------------------------------------------------------
Divide and Conquer Model:الفرق هنا عن اللي فوق الماتسر ما يجتاج انه يقس المشكله على نفس طبيعة المشكله الاساسية
This model solves a complex problem by
splitting it into smaller easier sub-problems.

The recursion stops at the base case in which
the sub-problem is solved directly.
--------------------------------------------------------------------------------
Dataflow:الفرق هنا انه في الكونيشكن  بلوك فيه  ديبندنسي  في المودلز اللي قبلهم مافيها ويمدينا نعرف وش البلوكز اللي تشتغل الباريل
The main concept of dataflow programming is to
divide the computation problem into multiple
disjoint functional blocks.
Each block solves part of the problem.
Blocks are connected to each other to.
