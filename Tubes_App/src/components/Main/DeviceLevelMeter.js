import React from 'react';
import {Image, StyleSheet, Text, View} from 'react-native';


function DeviceLevelMeter(props) {
    return (
        <View style={styles.bg}>
            <Image style={styles.icon} source={require('../../assets/icons/level/low.png')}/>
        </View>
    )
}

const styles = StyleSheet.create({
    bg: {
        marginLeft: 7
    },
    icon: {
        width: 25,
        height: 25
    }
})

export default DeviceLevelMeter;