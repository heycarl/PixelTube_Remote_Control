import { StatusBar } from 'expo-status-bar';
import React from 'react';
import { StyleSheet, Text, View } from 'react-native';

import Main from './src/screens/Main';

export default function App() {
  return (
    <View>
      <Main/>
      <StatusBar style="auto" />
    </View>
  );
}