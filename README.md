<!-- Dining Philosophers Project -->
<h1 style="font-size:2em; font-weight:bold;">Dining Philosophers Problem - Project 1</h1>

<h2 style="font-size:1.5em; font-weight:bold;">Project Description</h2>
<p>This project implements the classical concurrency problem <strong>Dining Philosophers Problem</strong> using C++11 with <code>std::thread</code> and custom synchronization mechanisms. The exercise demonstrates:</p>
<ul>
  <li><strong>Thread creation</strong></li>
  <li><strong>Handling critical sections</strong></li>
  <li><strong>Preventing deadlocks</strong> without using ready-made synchronization modules (e.g., <code>std::mutex</code>).</li>
</ul>
<p>Each philosopher (thread) alternates between thinking and eating, while competing for shared resources (forks). To avoid deadlock, a locking order is enforced on the forks (always acquire the lower-indexed fork first).</p>

<h2 style="font-size:1.5em; font-weight:bold;">Compilation and Execution</h2>
<p>
  <strong>Requirements:</strong> Compiler supporting C++11 (e.g., <code>g++</code>, <code>clang++</code>). You can compile the source manually or use the provided executable (<code>filozofowie.exe</code>) on Windows.
</p>
<p><strong>Option 1</strong> – Using Provided Executable (Windows only):</p>
<pre>
filozofowie.exe &lt;number_of_philosophers&gt;
</pre>
<p><strong>Option 2</strong> – Manual Compilation:</p>
<pre>
g++ -std=c++11 -pthread -o filozofowie filozofowie.cpp
./filozofowie &lt;number_of_philosophers&gt;
</pre>

<h2 style="font-size:1.5em; font-weight:bold;">Problem Description</h2>
<p>In the Dining Philosophers Problem, <strong>n philosophers</strong> sit around a round table with one fork between each pair. To eat, a philosopher needs both the fork on their left and the fork on their right. Philosophers alternate between thinking and eating and must never deadlock by waiting indefinitely for forks.</p>

<h2 style="font-size:1.5em; font-weight:bold;">Threads and Their Roles</h2>
<ul>
  <li><strong>Philosopher Threads:</strong> Each philosopher runs in its own thread and continuously:
    <ul>
      <li>Thinks (simulated with a random delay),</li>
      <li>Acquires both forks using custom spinlocks,</li>
      <li>Eats (simulated with another delay), and</li>
      <li>Releases the forks.</li>
    </ul>
  </li>
  <li><strong>Console Output:</strong> A separate global <code>SpinLock</code> is used to protect <code>std::cout</code> output from concurrent access.</li>
</ul>

<h2 style="font-size:1.5em; font-weight:bold;">Critical Sections and Their Handling</h2>
<ul>
  <li><strong>Fork Acquisition:</strong>
    <ul>
      <li><em>Shared Resource:</em> The forks, protected by custom spinlocks.</li>
      <li><em>Solution:</em> Philosophers always acquire the lower-indexed fork first (e.g., <code>if (leftFork > rightFork) { swap(leftFork, rightFork); }</code>).</li>
    </ul>
  </li>
  <li><strong>Console Output:</strong>
    <ul>
      <li><em>Critical Section:</em> Writing to <code>std::cout</code> is synchronized.</li>
      <li><em>Solution:</em> A global <code>SpinLock</code> (<code>coutLock</code>) and a <code>ScopedLock</code> wrapper (using RAII) prevent message interleaving.</li>
    </ul>
  </li>
</ul>

<hr>

<!-- Chat Project -->
<h1 style="font-size:2em; font-weight:bold;">Chat Project – Operating Systems 2</h1>

<h2 style="font-size:1.5em; font-weight:bold;">Project Description</h2>
<p>This project implements a chat application that allows multiple clients to communicate simultaneously. The system consists of the following modules:</p>
<ul>
  <li><strong>server.py:</strong> Handles incoming connections, message reception, and broadcasting messages to all connected clients.</li>
  <li><strong>client.py:</strong> Connects to the server and manages sending/receiving messages.</li>
  <li><strong>clientGUI.py:</strong> Provides a graphical user interface (using Tkinter) for user login and communication.</li>
  <li><strong>main.py:</strong> The entry point that starts the server.</li>
</ul>
<p>The project is written in Python and uses multi-threading and synchronization mechanisms to ensure correct handling of simultaneous connections.</p>

<h2 style="font-size:1.5em; font-weight:bold;">Execution Instructions</h2>
<p><strong>Server Execution:</strong></p>
<ol>
  <li>Open a terminal and navigate to the project directory.</li>
  <li>Run the server with:
    <pre>
python main.py
    </pre>
    The server listens for connections on port <strong>5050</strong>.
  </li>
</ol>
<p><strong>Client Execution:</strong></p>
<ol>
  <li>Open a new terminal (or use a different machine) and navigate to the project directory.</li>
  <li>Run the client GUI with:
    <pre>
python clientGUI.py
    </pre>
  </li>
  <li>Upon launch, a login screen appears. Enter your username to start chatting.</li>
</ol>

<h2 style="font-size:1.5em; font-weight:bold;">Problem Description</h2>
<p>The chat application addresses the classic inter-process communication challenge in a multi-threaded environment. The main issues include:</p>
<ul>
  <li><strong>Synchronizing access to shared resources:</strong> Ensuring data consistency for the list of active clients and the chat history.</li>
  <li><strong>Handling multi-threading:</strong> Each client connection is handled by a separate thread, requiring proper synchronization to prevent concurrent access issues.</li>
  <li><strong>Managing client disconnections:</strong> Ensuring that disconnected clients are removed from the active list to avoid sending messages to inactive connections.</li>
</ul>

<h2 style="font-size:1.5em; font-weight:bold;">Threads and Their Roles</h2>
<ul>
  <li><strong>On the Server:</strong> For each connected client, a dedicated thread (using the <code>receive_message</code> function in <code>server.py</code>) manages communication.</li>
  <li><strong>On the Client:</strong> The function <code>talk_to_server</code> in <code>client.py</code> starts a separate thread to listen for messages from the server, enabling simultaneous message sending and receiving via the GUI.</li>
</ul>

<h2 style="font-size:1.5em; font-weight:bold;">Critical Sections and Their Handling</h2>
<ul>
  <li><strong>Client List (<code>client_sockets</code>):</strong>
    <ul>
      <li><em>Critical Section:</em> Modifying the list of active connections.</li>
      <li><em>Solution:</em> A lock (<code>client_sockets_lock</code>) ensures that only one thread can modify the client list at a time.</li>
    </ul>
  </li>
  <li><strong>Chat History (<code>chat_history</code>):</strong>
    <ul>
      <li><em>Critical Section:</em> Updating and reading the chat history.</li>
      <li><em>Solution:</em> A lock (<code>chat_history_lock</code>) protects the chat history against simultaneous access from multiple threads.</li>
    </ul>
  </li>
</ul>
