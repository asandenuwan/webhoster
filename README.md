<center><h1>WebHoster</h1></center>
<center><h3>A lightweight local web server built using C++</h3></center>
<hr>

<h2>🚀 Features</h2>
<ul>
  <li>Serve static websites instantly from your local machine.</li>
  <li>Zero configuration — portable single executable.</li>
  <li>Supports HTML, CSS, JS, images, and other static files.</li>
  <li>Local network access through your IP address.</li>
  <li>Ideal for testing, previewing, or demo websites.</li>
</ul>

<hr>

<h2>🛠️ Requirements</h2>
<ul>
  <li>Windows / Linux / macOS</li>
  <li>Compiled <code>WebHoster.exe</code> (or respective binary)</li>
  <li>Network permission (firewall/antivirus)</li>
</ul>

<hr>

<h2>📦 Installation & Setup</h2>
<ol>
  <li>Download or clone the repository.</li>
  <li>Place <code>WebHoster.exe</code> inside the folder containing your website files.</li>
  <li>Run the executable.</li>
  <li>Allow any network permission requests.</li>
</ol>

<hr>

<h2>▶️ Running the Server</h2>
<ol>
  <li>Launch <code>WebHoster.exe</code>.</li>
  <li>Click the <strong>Start Server</strong> button.</li>
  <li>Open your browser and enter your IP address.</li>
  <li>To find your IP on Windows, run:</li>
</ol>

<pre>
ipconfig
</pre>

<p>If no network is available, use the loopback address:</p>

<pre>
127.0.0.1
</pre>

<p>The server will automatically load <code>index.html</code> (must be in the same folder).</p>

<hr>

<h2>🧱 Architecture</h2>

<pre>
+------------------+
|   WebHoster.exe  | → Embedded local HTTP server
+---------+--------+
          |
          v
+------------------+
| Web Directory    | → Contains index.html, CSS, JS, images
+------------------+
</pre>

<hr>

<h2>⚙️ How It Works</h2>
<ol>
  <li>The internal server listens for incoming HTTP requests.</li>
  <li>When the browser requests a file, the app reads it from the directory.</li>
  <li>MIME type is detected and the file is sent back to the browser.</li>
  <li>If a file is missing or invalid, a 404 response may be returned.</li>
</ol>

<hr>

<h2>🚑 Troubleshooting</h2>

<ul>
  <li><strong>Server won't start?</strong><br>
      Check if another app is using the same port or run as administrator.</li>

  <li><strong>Browser can't reach IP?</strong><br>
      Confirm your correct IP via <code>ipconfig</code>.</li>

  <li><strong>Index page not loading?</strong><br>
      Ensure <code>index.html</code> exists in the same folder.</li>

  <li><strong>Firewall blocking?</strong><br>
      Allow the app through Windows Firewall.</li>
</ul>

<hr>

<h2>💡 Future Improvements</h2>
<ul>
  <li>Add port configuration UI</li>
  <li>Add HTTPS with certificates</li>
  <li>Enable directory browsing</li>
  <li>Add logging system</li>
  <li>Custom default page support</li>
</ul>

<hr>

<h2>📜 License</h2>
<p>This project is released under the <strong>MIT License</strong>.</p>

<hr>

<h2>✉️ Contact</h2>
<p>Created by <strong>Asan Denuwan</strong>. Feedback and contributions are welcome!</p>

