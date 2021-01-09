import React from 'react';
import { StyleSheet, Text, View } from 'react-native';


function DeviceID(props) {
    return (
        <View style={styles.bg}>
            <Text style={styles.text}>{props.id}</Text>
        </View>
    )
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

export default DeviceID;

