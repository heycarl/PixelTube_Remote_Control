import React, { useState } from 'react';
import {ScrollView, StyleSheet, Text, View} from 'react-native';

import NetInfo from "@react-native-community/netinfo";
import Device from "./Device";
const axios = require('axios');

function Devices(props) {    
    const [devices, setDevices] = useState([{radio_level: "NO_VALUE"}])
    function scan_devices(){
        scan_devices().then(tubes => {
            setDevices(tubes)
        })
    }
    setInterval(scan_devices, 5000)
    return (
        <View>
            <ScrollView>
                {
                    devices.map((data, index) => {
                        return (
                           <Text key={index}>{data['radio_level']}</Text>
                        )
                    })
                }
            </ScrollView>
        </View> 
    )
}


async function scan_devices() {
    let devices = []
    const a = await NetInfo.fetch().then(info => {
        return info.details.ipAddress
    })
    try {
        const b = a.split(".").splice(0,3).join(".")
        for (let i = 218; i < 231; i++) {
            const url = 'http://' + b + '.' + i.toString() + '/settings'
            try {
                const resp = await axios.get(url, {
                    timeout: 100
                })
                if (resp.data['working_mode'] !== undefined) {
                    devices.push(resp.data)
                }
            } catch (e) {
                // console.log("Time exceeded for " + url);
            }
        }
        return devices
    } catch (e) {
        return devices
    }

}

export default Devices;