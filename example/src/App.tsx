import { Text, View, StyleSheet } from 'react-native';
import { HttpServer } from '@op-engineering/op-server';

let server = new HttpServer();
server.get('/ping', async (req: any, res: any) => {
  // res.text('pong');
  // return 'pong';
  throw new Error('Blah');
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
