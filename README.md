<h1>Library Management System</h1>

<h2>Description</h2>
<p>
  A Console-based Library Management System using C++, MongoDB, Node.js, Express.js, and CMake.
</p>

<h2>Features</h2>
<ul>
  <li>Hybrid backend combining C++ logic with Node.js API for database access.</li>
  <li>Stores and retrieves data from MongoDB with secure and efficient queries.</li>
  <li>Cross-platform support with easy setup using CMake.</li>
  <li>Environment variables managed using Dotenv for flexible configuration.</li>
</ul>

<h2>Requirements</h2>
<ul>
  <li>C++ 20</li>
  <li>Node.JS 18.19</li>
  <li>Express.JS 4.19.2</li>
  <li>MongoDB v4.17</li>
  <li>CMake 3.28</li>
  <li>npm 9.2</li>
  <li>Mongoose 8.5</li>
  <li>Dotenv 10.0.0</li>
  <li>Terminal or Command Prompt</li>
</ul>

<h2>Steps to Run</h2>
<ol>
  <li>
    <h4>Install Dependencies</h4>
    <p>Use the package manager to install all required Node modules and set up C++ tools.</p>
    <code>npm install</code>
  </li>
  <li>
    <h4>Configure Environment</h4>
    <p>Create a <code>.env</code> file with your MongoDB URI and other required variables.</p>
  </li>
  <li>
    <h4>Build and Run</h4>
    <p>Use CMake to build the C++ component and start the Node.js server:</p>
    <code>cmake . && make && node index.js</code>
  </li>
</ol>

<h2>Usage</h2>
<p>
  Use the terminal to interact with the console app. Backend Node.js server handles all MongoDB operations. Designed for educational use and backend logic demos.
</p>

<h2>Future Scope</h2>
<ul>
  <li>Add GUI interface using React or Electron.</li>
  <li>Integrate authentication and access control.</li>
  <li>Improve error handling and logging system.</li>
  <li>Export data to CSV or PDF.</li>
</ul>

<h2>Author</h2>
<p>
  Crafted by <a href="https://github.com/Melvin-Shalom">Melvin Shalom</a> with ❤️ and <code>CMake</code> wizardry.
</p>

<h2>License</h2>
<p>
  Licensed under the <a href="https://opensource.org/licenses/MIT">MIT License</a>
</p>
