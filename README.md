# @op-engineering/op-server

Fast HTTP Server for React Native

## Installation

```sh
npm install @op-engineering/op-server
```

## Usage

## Request Object

The Request object is **read-only** and contains information about the incoming HTTP request.

### Properties

- `method: string` - The HTTP method (GET, POST, PUT, DELETE, etc.)
- `path: string` - The request path (e.g., "/api/users")
- `body: string` - The request body content
- `headers: Record<string, string>` - HTTP headers from the request
- `params: Record<string, string>` - Query string parameters

### Example

```typescript
server.get('/api/user', async (req, res) => {
  console.log(req.method); // "GET"
  console.log(req.path); // "/api/user"
  console.log(req.params); // { id: "123" } if URL was /api/user?id=123
  console.log(req.headers); // { "user-agent": "...", ... }

  res.statusCode = 200;
  res.content = 'User data';
});
```

## Response Object

The Response object is **writable** and allows you to set the HTTP response from JavaScript.

### Properties

- `statusCode: number` - HTTP status code (default: 200)
- `content: string` - Response body content
- `contentType: string` - Content-Type header (default: "text/plain")
- `headers: Record<string, string>` - Custom response headers (read-only, use `setHeader` to add)

### Methods

- `setHeader(key: string, value: string): void` - Add a custom header to the response

### Example

```typescript
// Simple text response
server.get('/ping', async (_req, res) => {
  res.statusCode = 200;
  res.contentType = 'text/plain';
  res.content = 'pong';
});

// JSON response
server.get('/api/data', async (req, res) => {
  res.statusCode = 200;
  res.contentType = 'application/json';
  res.content = JSON.stringify({
    success: true,
    data: { id: 1, name: 'Example' },
  });
});

// Custom headers
server.get('/custom', async (_req, res) => {
  res.statusCode = 200;
  res.contentType = 'application/json';
  res.setHeader('X-Custom-Header', 'CustomValue');
  res.setHeader('Cache-Control', 'no-cache');
  res.content = JSON.stringify({ message: 'OK' });
});

// Error response
server.get('/error', async (_req, res) => {
  res.statusCode = 404;
  res.contentType = 'application/json';
  res.content = JSON.stringify({ error: 'Not found' });
});
```

## Error Handling

If your handler throws an error, the server will automatically:

1. Set `statusCode` to 500
2. Set `content` to the error message
3. Use the error's message property if available

```typescript
server.get('/error', async () => {
  throw new Error('Something went wrong'); // Will return 500 with error message
});
```

## Complete Example

```typescript
import { HttpServer } from '@op-engineering/op-server';

const server = new HttpServer();

// GET with query params
server.get('/user', async (req, res) => {
  const userId = req.params.id;

  res.statusCode = 200;
  res.contentType = 'application/json';
  res.content = JSON.stringify({
    id: userId,
    name: 'John Doe',
  });
});

// POST with body
server.POST('/user', async (req, res) => {
  const userData = JSON.parse(req.body);

  res.statusCode = 201;
  res.contentType = 'application/json';
  res.setHeader('Location', '/user/123');
  res.content = JSON.stringify({
    success: true,
    created: userData,
  });
});

// Start server on port 3000
server.listen(3000);
```

## HTTPs

Support is possible but not implemented. Pay me to do it :)

## License

MIT
