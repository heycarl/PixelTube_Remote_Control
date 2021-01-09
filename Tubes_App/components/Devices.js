import React, { useState } from 'react';
import { StyleSheet, Text, View } from 'react-native';
import NetInfo from "@react-native-community/netinfo";

function Devices(props) {    
    const [devices, setDevices] = useState([])
    // scan_devices().then(info => {
    //     setDevices(info)
    // })
    return (    
        <View>
            <Text>Current connection type is</Text>
        </View> 
    )
}


// async function scan_devices() {
//     await NetInfo.fetch().then(info => {
//         subnet = info.details.ipAddress
//         return subnet
//     })
// }

export default Devices;