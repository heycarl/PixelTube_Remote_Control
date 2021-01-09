import React from 'react';
import { StyleSheet, Text, View } from 'react-native';
import Devices from "../components/Main/Devices";
import Header from "../components/common/Header";


function Main(props) {
    return (
        <View>
            <Header text="PixelTube Controller"/>
            <Devices/>
        </View>
    )
}

export default Main;
