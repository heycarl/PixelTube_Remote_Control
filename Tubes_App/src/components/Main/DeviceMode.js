import React from 'react';
import { StyleSheet, Text, View } from 'react-native';


function DeviceMode(props) {
    if (props.mode === false) {
        return (
            <View style={styles.bg}>
                <Text style={styles.text}>DMX</Text>
            </View>
        )
    } else if (props.mode === true){
        return (
            <View style={styles.bg}>
                <Text style={styles.text}>Manual</Text>
            </View>
        )
    } else {
        return (
            <View style={styles.bg}>
                <Text style={styles.text}>NO_MODE</Text>
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
        backgroundColor: '#EDEDED',
        borderRadius: 4,
        marginLeft: 7,
        justifyContent: 'center',
    }
})

export default DeviceMode;

