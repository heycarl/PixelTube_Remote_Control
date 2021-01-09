import React, {useState} from 'react';
import { StyleSheet, Text, View } from 'react-native';
import DeviceAddress from "./DeviceAddress";
import DeviceLevelMeter from "./DeviceLevelMeter";
import DeviceID from "./DeviceID";
import DeviceMode from "./DeviceMode";
const axios = require('axios');

function Header(props) {
    const [device_data, setData] = useState({
        level: -200,
        id: "NO_ID",
        mode: "NO_MODE",
        address: "NO_ADDR",
        rgb: [0, 0, 0]
    })

    function get_data_from_device() {
        const url = 'http://' + props.ip + '/settings'
        axios.get(url, {
            timeout: 800
        }).then((resp) => {
            setData({
                level: resp.data['radio_level'],
                id: "pixel-01",
                mode: resp.data['working_mode'],
                address: resp.data['universe'].toString() + '.' + resp.data['address'],
                rgb: [resp.data['r'], resp.data['g'], resp.data['b']]
            })
        })
    }
    setInterval(get_data_from_device, 10000)

    return (
            <View style={styles.device}>
                <View style={styles.device_status}>
                    <DeviceLevelMeter level={device_data.level} />
                    <DeviceID id={device_data.id}/>
                    <DeviceMode mode={device_data.mode}/>
                    <DeviceAddress mode={device_data.mode} color={device_data.rgb} address={device_data.address}/>
                </View>
            </View>
    )
}

const styles = StyleSheet.create({
    device: {
        height: 60,
        alignItems: 'flex-start',
        justifyContent: 'center',
        borderWidth: 4,
        borderColor: '#00FF66',
        borderRadius: 10,
        marginRight: 25,
        marginLeft: 25,
        marginTop: 10,
    },
    device_status: {
        flexDirection: 'row',
    }
})


export default Header;