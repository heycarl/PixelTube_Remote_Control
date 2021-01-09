import { StatusBar } from 'expo-status-bar';
import React from 'react';
import { StyleSheet, Text, View } from 'react-native';
import Devices from './components/Devices';

import Header from './components/Header'

export default function App() {
  return (
    <View style={styles.container}>
      <Header name="Sasha"/>
      <Devices/>
      <StatusBar style="auto" />  
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});
