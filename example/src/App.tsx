import { Text, View, StyleSheet } from 'react-native';
import { HttpServer } from '@op-engineering/op-server';

let server = new HttpServer();

// Example GET endpoint
server.get('/ping', async (_req, res) => {
  res.statusCode = 200;
  res.contentType = 'text/plain';
  res.content = 'pong';
});

// Example POST endpoint with JSON response
server.POST('/api/data', async (req, res) => {
  res.statusCode = 200;
  res.contentType = 'application/json';
  res.content = JSON.stringify({
    message: 'Data received',
    body: req.body,
    method: req.method,
    path: req.path,
  });
});

// Example with custom headers
server.get('/headers', async (req, res) => {
  res.statusCode = 200;
  res.contentType = 'application/json';
  res.setHeader('X-Custom-Header', 'CustomValue');
  res.content = JSON.stringify({
    receivedHeaders: req.headers,
    queryParams: req.params,
  });
});

// Example error handling
server.get('/error', async () => {
  throw new Error('This is an intentional error');
});

server.listen(3000);

export default function App() {
  return (
    <View style={styles.container}>
      <Text>ServerStarted</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
});
