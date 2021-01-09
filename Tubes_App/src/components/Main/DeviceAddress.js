import React from 'react';
import { StyleSheet, Text, View } from 'react-native';


function DeviceAddress(props) {
    if (props.mode === 0) {
        return (
            <View style={styles.bg}>
                <Text style={styles.text}>{props.universe}.{props.address}</Text>
            </View>
        )
    } else if (props.mode === 1) {
        return (
            <View style={styles.sq}>
            </View>
        )
    } else {
        return (
            <View style={styles.bg}>
                <Text style={styles.text}>NO_ADDR</Text>
            </View>
        )
    }
}

const styles = StyleSheet.create({
    text: {
        fontSize: 17,
        marginRight: 3,
        marginLeft: 3,
        marginTop: 0,
        marginBottom: 0,
    },
    bg: {
        backgroundColor: '#ededed',
        borderRadius: 4,
        marginLeft: 7,
        justifyContent: 'center',
    },
    sq: {
        backgroundColor: 'red',
        borderRadius: 4,
        width: '5%',
        height: '100%',
        marginLeft: 7
    }
})

export default DeviceAddress;