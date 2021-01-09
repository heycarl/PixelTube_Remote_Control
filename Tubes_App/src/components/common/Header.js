import React from 'react';
import { StyleSheet, Text, View } from 'react-native';


function Header(props) {
    return (
        <View style={styles.header}>
            <Text style={styles.text}>{props.text}</Text>
        </View>
    )
}

const styles = StyleSheet.create({
    header: {
        height: 70,
        alignItems: 'center',
        justifyContent: 'flex-end',
        paddingBottom: 10,
        borderBottomWidth: 4,
        borderBottomColor: '#0F62FE'
    },
    text: {
        fontSize: 20
    }
})

export default Header;