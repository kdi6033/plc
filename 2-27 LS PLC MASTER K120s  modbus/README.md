# LS PLC MASTER K120s  modbus    
[김동일교수 유튜브보기](http://i2r.link)

### 2-27-1 node red program
node red로 plc 프로토콜을 만들어 입력을 모니터링 하고 출력을 제어한다.     
```
[
    {
        "id": "81c4951e7d906372",
        "type": "debug",
        "z": "0981fdccc9de072a",
        "name": "",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "statusVal": "",
        "statusType": "auto",
        "x": 350,
        "y": 100,
        "wires": []
    },
    {
        "id": "e2043b637b724e4a",
        "type": "serial in",
        "z": "0981fdccc9de072a",
        "name": "",
        "serial": "63957752.49a888",
        "x": 210,
        "y": 100,
        "wires": [
            [
                "81c4951e7d906372"
            ]
        ]
    },
    {
        "id": "94b94c351050a97c",
        "type": "serial out",
        "z": "0981fdccc9de072a",
        "name": "",
        "serial": "63957752.49a888",
        "x": 670,
        "y": 180,
        "wires": []
    },
    {
        "id": "fb3dccaf0d4f6c74",
        "type": "function",
        "z": "0981fdccc9de072a",
        "name": "modbus cal",
        "func": "var auchCRCHi = [\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40\n      ];\n\n      /* Table of CRC values for low-order byte */\n    var auchCRCLo = [\n        0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,\n        0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,\n        0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,\n        0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,\n        0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,\n        0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,\n        0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,\n        0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,\n        0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,\n        0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,\n        0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,\n        0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,\n        0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,\n        0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,\n        0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,\n        0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,\n        0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,\n        0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,\n        0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,\n        0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,\n        0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,\n        0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,\n        0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,\n        0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,\n        0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,\n        0x43, 0x83, 0x41, 0x81, 0x80, 0x40\n      ];\n\nvar nTemp;\nvar wCRCWord = 0xFFFF;\ndata=msg.payload;\nvar len=msg.payload.length-2;\nvar crc = [0xFF, 0xFF];\n    var nextByte = 0;\n    var uIndex; /* will index into CRC lookup*/ /* table */\n    /* pass through message buffer */\n    for (var i = 0; i < len && i < data.length; i++) {\n      nextByte = 0xFF & (data[i]);\n      uIndex = crc[0] ^ nextByte; //*puchMsg++; /* calculate the CRC */\n      crc[0] = crc[1] ^ auchCRCHi[uIndex];\n      crc[1] = auchCRCLo[uIndex];\n    }\n\ndata[len]=crc[0];\ndata[len+1]=crc[1];\nmsg.payload= data;\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "x": 490,
        "y": 180,
        "wires": [
            [
                "94b94c351050a97c"
            ]
        ]
    },
    {
        "id": "b72de589a7ebb03d",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "출력 비트 읽기-1",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,1,0,64,0,20,0,0]",
        "payloadType": "bin",
        "x": 260,
        "y": 180,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "029e5100d4214ca0",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "비트 개별 쓰기 on - 5",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,5,0,64,255,0,0,0]",
        "payloadType": "bin",
        "x": 280,
        "y": 280,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "8d25fc94e1dc2e53",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "비트 개별 쓰기 off - 5",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,5,0,64,0,0,0,0]",
        "payloadType": "bin",
        "x": 280,
        "y": 320,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "7ca472d76232538a",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "워드 개별 쓰기 - 6",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,6,0,4,0,255,0,0]",
        "payloadType": "bin",
        "x": 270,
        "y": 360,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "e269778788d668a5",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "비트 연속 쓰기 on - 15",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,15,0,64,0,10,2,255,0,0,0]",
        "payloadType": "bin",
        "x": 280,
        "y": 460,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "ff0ea8ef1ddd9ba7",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "비트 연속 쓰기 off - 15",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,15,0,64,0,10,2,0,0,0,0]",
        "payloadType": "bin",
        "x": 280,
        "y": 500,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "5910fdc2a33f074b",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "입력 비트 읽기-2",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,2,0,0,0,20,0,0]",
        "payloadType": "bin",
        "x": 260,
        "y": 220,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "2ac63ca411b4adef",
        "type": "inject",
        "z": "0981fdccc9de072a",
        "name": "워드 개별 쓰기 - 6",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "[1,6,0,4,0,0,0,0]",
        "payloadType": "bin",
        "x": 270,
        "y": 400,
        "wires": [
            [
                "fb3dccaf0d4f6c74"
            ]
        ]
    },
    {
        "id": "63957752.49a888",
        "type": "serial-port",
        "serialport": "COM6",
        "serialbaud": "19200",
        "databits": "8",
        "parity": "none",
        "stopbits": "1",
        "waitfor": "",
        "dtr": "none",
        "rts": "none",
        "cts": "none",
        "dsr": "none",
        "newline": "100",
        "bin": "bin",
        "out": "time",
        "addchar": "",
        "responsetimeout": "10000"
    }
]
```

### 2-27-2 node red program
node red 에서 연속적인 비트제어로 plc를 읽고 쓰기를 한다.
```
[
    {
        "id": "6e1b7177bd2b9adb",
        "type": "ui_led",
        "z": "0cbe32a84bfc5a9c",
        "order": 2,
        "group": "7ac6f0a21739dc93",
        "width": "2",
        "height": "1",
        "label": "q00",
        "colorForValue": [
            {
                "color": "#808080",
                "value": "0",
                "valueType": "str"
            },
            {
                "color": "#008000",
                "value": "1",
                "valueType": "str"
            }
        ],
        "allowColorForValueInMessage": false,
        "shape": "circle",
        "showGlow": true,
        "name": "q00",
        "x": 570,
        "y": 180,
        "wires": []
    },
    {
        "id": "c6fc08f99d5c22b2",
        "type": "function",
        "z": "0cbe32a84bfc5a9c",
        "name": "디코드",
        "func": "//var dec = msg.payload.charAt(13);\nvar dec=msg.payload[3];\nvar bin = parseInt(dec).toString(2);\nbin=\"00000000\"+bin;\nbin = bin.slice(-8);\nmsg.payload=bin;\n\n//dec = msg.payload.charAt(12);\n//var bin1 = parseInt(dec).toString(2);\n//bin1=\"0000\"+bin1;\n//bin1 = bin1.slice(-4);\n\n//msg.payload=bin1+bin;\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "x": 228.9374885559082,
        "y": 293.10755443573,
        "wires": [
            [
                "caf1ef52cd963f85"
            ]
        ]
    },
    {
        "id": "caf1ef52cd963f85",
        "type": "function",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "func": "var out=[];\nout.push({payload:msg.payload.charAt(7)});\nout.push({payload:msg.payload.charAt(6)});\nout.push({payload:msg.payload.charAt(5)});\nout.push({payload:msg.payload.charAt(4)});\nout.push({payload:msg.payload.charAt(3)});\nout.push({payload:msg.payload.charAt(2)});\nout.push({payload:msg.payload.charAt(1)});\nout.push({payload:msg.payload.charAt(0)});\nreturn [out[0],out[1],out[2],out[3],out[4],out[5],out[6],out[7]];\n",
        "outputs": 8,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 371.9930877685547,
        "y": 293.96174812316895,
        "wires": [
            [
                "6e1b7177bd2b9adb"
            ],
            [
                "2c4e5e85a7296bd5"
            ],
            [
                "a12852caeb9f2c15"
            ],
            [
                "6a88d35d43f1bc8e"
            ],
            [
                "c05b58979394d6eb"
            ],
            [
                "848be5924e24495e"
            ],
            [],
            []
        ]
    },
    {
        "id": "2c4e5e85a7296bd5",
        "type": "ui_led",
        "z": "0cbe32a84bfc5a9c",
        "order": 3,
        "group": "7ac6f0a21739dc93",
        "width": "2",
        "height": "1",
        "label": "q01",
        "colorForValue": [
            {
                "color": "#808080",
                "value": "0",
                "valueType": "str"
            },
            {
                "color": "#008000",
                "value": "1",
                "valueType": "str"
            }
        ],
        "allowColorForValueInMessage": false,
        "shape": "circle",
        "showGlow": true,
        "name": "q01",
        "x": 571.9375343322754,
        "y": 222.10753631591797,
        "wires": []
    },
    {
        "id": "a12852caeb9f2c15",
        "type": "ui_led",
        "z": "0cbe32a84bfc5a9c",
        "order": 4,
        "group": "7ac6f0a21739dc93",
        "width": "2",
        "height": "1",
        "label": "q02",
        "colorForValue": [
            {
                "color": "#808080",
                "value": "0",
                "valueType": "str"
            },
            {
                "color": "#008000",
                "value": "1",
                "valueType": "str"
            }
        ],
        "allowColorForValueInMessage": false,
        "shape": "circle",
        "showGlow": true,
        "name": "q02",
        "x": 571.9375343322754,
        "y": 262.10753631591797,
        "wires": []
    },
    {
        "id": "6a88d35d43f1bc8e",
        "type": "ui_led",
        "z": "0cbe32a84bfc5a9c",
        "order": 5,
        "group": "7ac6f0a21739dc93",
        "width": "2",
        "height": "1",
        "label": "q03",
        "colorForValue": [
            {
                "color": "#808080",
                "value": "0",
                "valueType": "str"
            },
            {
                "color": "#008000",
                "value": "1",
                "valueType": "str"
            }
        ],
        "allowColorForValueInMessage": false,
        "shape": "circle",
        "showGlow": true,
        "name": "q03",
        "x": 571.9375343322754,
        "y": 301.1075668334961,
        "wires": []
    },
    {
        "id": "c05b58979394d6eb",
        "type": "ui_led",
        "z": "0cbe32a84bfc5a9c",
        "order": 6,
        "group": "7ac6f0a21739dc93",
        "width": "2",
        "height": "1",
        "label": "q04",
        "colorForValue": [
            {
                "color": "#808080",
                "value": "0",
                "valueType": "str"
            },
            {
                "color": "#008000",
                "value": "1",
                "valueType": "str"
            }
        ],
        "allowColorForValueInMessage": false,
        "shape": "circle",
        "showGlow": true,
        "name": "q04",
        "x": 574.9375343322754,
        "y": 340.1075668334961,
        "wires": []
    },
    {
        "id": "848be5924e24495e",
        "type": "ui_led",
        "z": "0cbe32a84bfc5a9c",
        "order": 7,
        "group": "7ac6f0a21739dc93",
        "width": "2",
        "height": "1",
        "label": "q05",
        "colorForValue": [
            {
                "color": "#808080",
                "value": "0",
                "valueType": "str"
            },
            {
                "color": "#008000",
                "value": "1",
                "valueType": "str"
            }
        ],
        "allowColorForValueInMessage": false,
        "shape": "circle",
        "showGlow": true,
        "name": "q05",
        "x": 573.9375343322754,
        "y": 385.1075668334961,
        "wires": []
    },
    {
        "id": "5b98e27de8a8b15f",
        "type": "function",
        "z": "0cbe32a84bfc5a9c",
        "name": "읽기",
        "func": "\nvar auto = global.get('auto') || 0;\nif(auto !=0) {\n    buf=[1,2,0,0,0,8,0,0];\n    msg.payload=buf;\n    return msg;\n}",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 370,
        "y": 100,
        "wires": [
            [
                "82ba0e00d5551bb5"
            ]
        ]
    },
    {
        "id": "82ba0e00d5551bb5",
        "type": "function",
        "z": "0cbe32a84bfc5a9c",
        "name": "modbus cal",
        "func": "var auchCRCHi = [\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40\n      ];\n\n      /* Table of CRC values for low-order byte */\n    var auchCRCLo = [\n        0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,\n        0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,\n        0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,\n        0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,\n        0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,\n        0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,\n        0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,\n        0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,\n        0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,\n        0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,\n        0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,\n        0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,\n        0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,\n        0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,\n        0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,\n        0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,\n        0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,\n        0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,\n        0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,\n        0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,\n        0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,\n        0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,\n        0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,\n        0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,\n        0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,\n        0x43, 0x83, 0x41, 0x81, 0x80, 0x40\n      ];\n\n//var data=Buffer.from([1,15,0,0,0,10,2,255,0,0,0]);\nvar data=Buffer.from(msg.payload);\nvar nTemp;\nvar wCRCWord = 0xFFFF;\n//data=msg.payload;\nvar len=data.length-2;\nvar crc = [0xFF, 0xFF];\n    var nextByte = 0;\n    var uIndex; /* will index into CRC lookup*/ /* table */\n    /* pass through message buffer */\n    for (var i = 0; i < len && i < data.length; i++) {\n      nextByte = 0xFF & (data[i]);\n      uIndex = crc[0] ^ nextByte; //*puchMsg++; /* calculate the CRC */\n      crc[0] = crc[1] ^ auchCRCHi[uIndex];\n      crc[1] = auchCRCLo[uIndex];\n    }\n\ndata[len]=crc[0];\ndata[len+1]=crc[1];\nmsg.payload= data;\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "x": 518.0000152587891,
        "y": 98.99998664855957,
        "wires": [
            [
                "dfb5a99c740dc9d5"
            ]
        ]
    },
    {
        "id": "d693e9f385880233",
        "type": "inject",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "2",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payloadType": "date",
        "x": 230,
        "y": 100,
        "wires": [
            [
                "5b98e27de8a8b15f"
            ]
        ]
    },
    {
        "id": "dfb5a99c740dc9d5",
        "type": "serial request",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "serial": "63957752.49a888",
        "x": 670,
        "y": 100,
        "wires": [
            [
                "c6fc08f99d5c22b2"
            ]
        ]
    },
    {
        "id": "dd41b6823f696976",
        "type": "comment",
        "z": "0cbe32a84bfc5a9c",
        "name": "참조메뉴얼",
        "info": "LS산전 \"사용설명서_XGB Cnet_V1.8.pdf\"\n9-8 페이지\n9.4.2 비트 입력영역에 비트형식의 데이터 읽기(02) ",
        "x": 200,
        "y": 60,
        "wires": []
    },
    {
        "id": "1059c51b00e97ec6",
        "type": "comment",
        "z": "0cbe32a84bfc5a9c",
        "name": "잠조유튜브",
        "info": "https://youtu.be/yR153KZJVno",
        "x": 200,
        "y": 200,
        "wires": []
    },
    {
        "id": "53d16f2e2071927d",
        "type": "ui_switch",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "label": "모니터링",
        "tooltip": "",
        "group": "7ac6f0a21739dc93",
        "order": 1,
        "width": "0",
        "height": "0",
        "passthru": true,
        "decouple": "false",
        "topic": "",
        "topicType": "str",
        "style": "",
        "onvalue": "1",
        "onvalueType": "num",
        "onicon": "",
        "oncolor": "",
        "offvalue": "0",
        "offvalueType": "num",
        "officon": "",
        "offcolor": "",
        "animate": true,
        "x": 380,
        "y": 40,
        "wires": [
            [
                "8194346f589cc3fa"
            ]
        ]
    },
    {
        "id": "8194346f589cc3fa",
        "type": "function",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "func": "global.set(\"auto\",msg.payload);\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 520,
        "y": 40,
        "wires": [
            []
        ]
    },
    {
        "id": "3fee145403ca2c09",
        "type": "ui_switch",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "label": "i00",
        "tooltip": "",
        "group": "7ac6f0a21739dc93",
        "order": 10,
        "width": "2",
        "height": "1",
        "passthru": true,
        "decouple": "false",
        "topic": "",
        "topicType": "str",
        "style": "",
        "onvalue": "1",
        "onvalueType": "num",
        "onicon": "",
        "oncolor": "",
        "offvalue": "0",
        "offvalueType": "num",
        "officon": "",
        "offcolor": "",
        "animate": true,
        "x": 190,
        "y": 460,
        "wires": [
            [
                "6cf6d03862a54078"
            ]
        ]
    },
    {
        "id": "1e294f38faafa137",
        "type": "ui_switch",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "label": "i01",
        "tooltip": "",
        "group": "7ac6f0a21739dc93",
        "order": 11,
        "width": "2",
        "height": "1",
        "passthru": true,
        "decouple": "false",
        "topic": "",
        "topicType": "str",
        "style": "",
        "onvalue": "1",
        "onvalueType": "num",
        "onicon": "",
        "oncolor": "",
        "offvalue": "0",
        "offvalueType": "num",
        "officon": "",
        "offcolor": "",
        "animate": true,
        "x": 189.99999237060547,
        "y": 513.000020980835,
        "wires": [
            [
                "af922104fb1d9885"
            ]
        ]
    },
    {
        "id": "6a0ec12b74bea4ca",
        "type": "ui_switch",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "label": "i02",
        "tooltip": "",
        "group": "7ac6f0a21739dc93",
        "order": 12,
        "width": "2",
        "height": "1",
        "passthru": true,
        "decouple": "false",
        "topic": "",
        "style": "",
        "onvalue": "1",
        "onvalueType": "num",
        "onicon": "",
        "oncolor": "",
        "offvalue": "0",
        "offvalueType": "num",
        "officon": "",
        "offcolor": "",
        "x": 187.99999237060547,
        "y": 573.000020980835,
        "wires": [
            [
                "caa1081d82ddb6f4"
            ]
        ]
    },
    {
        "id": "6e544da2a2945871",
        "type": "ui_switch",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "label": "i03",
        "tooltip": "",
        "group": "7ac6f0a21739dc93",
        "order": 13,
        "width": "2",
        "height": "1",
        "passthru": true,
        "decouple": "false",
        "topic": "",
        "style": "",
        "onvalue": "1",
        "onvalueType": "num",
        "onicon": "",
        "oncolor": "",
        "offvalue": "0",
        "offvalueType": "num",
        "officon": "",
        "offcolor": "",
        "x": 186.99999237060547,
        "y": 624.000020980835,
        "wires": [
            [
                "d5d853b24ca893f9"
            ]
        ]
    },
    {
        "id": "6cf6d03862a54078",
        "type": "function",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "func": "global.set(\"i00\",msg.payload);\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 332.98038482666016,
        "y": 460.99610805511475,
        "wires": [
            [
                "23bcc4a0ed322a3b"
            ]
        ]
    },
    {
        "id": "af922104fb1d9885",
        "type": "function",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "func": "global.set(\"i01\",msg.payload);\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 331.98038482666016,
        "y": 513.9961080551147,
        "wires": [
            [
                "23bcc4a0ed322a3b"
            ]
        ]
    },
    {
        "id": "caa1081d82ddb6f4",
        "type": "function",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "func": "global.set(\"i02\",msg.payload);\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "x": 333.98038482666016,
        "y": 572.9961080551147,
        "wires": [
            [
                "23bcc4a0ed322a3b"
            ]
        ]
    },
    {
        "id": "d5d853b24ca893f9",
        "type": "function",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "func": "global.set(\"i03\",msg.payload);\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "x": 336.06591033935547,
        "y": 623.4826946258545,
        "wires": [
            [
                "23bcc4a0ed322a3b"
            ]
        ]
    },
    {
        "id": "23bcc4a0ed322a3b",
        "type": "function",
        "z": "0cbe32a84bfc5a9c",
        "name": "쓰기",
        "func": "var i00=global.get(\"i00\")||0;\nvar i01=global.get(\"i01\")||0;\nvar i02=global.get(\"i02\")||0;\nvar i03=global.get(\"i03\")||0;\nvar buf = Buffer.alloc(11);\nbuf=[1,15,0,64,0,10,2,255,0,0,0];\nbuf[7]=i00*1+i01*2+i02*4+i03*8;\n\nmsg.payload=buf;\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 501.99998474121094,
        "y": 461.00001335144043,
        "wires": [
            [
                "8f15da0feaf3804c"
            ]
        ]
    },
    {
        "id": "a6458f925124e27f",
        "type": "serial out",
        "z": "0cbe32a84bfc5a9c",
        "name": "",
        "serial": "63957752.49a888",
        "x": 810,
        "y": 460,
        "wires": []
    },
    {
        "id": "8f15da0feaf3804c",
        "type": "function",
        "z": "0cbe32a84bfc5a9c",
        "name": "modbus cal",
        "func": "var auchCRCHi = [\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40\n      ];\n\n      /* Table of CRC values for low-order byte */\n    var auchCRCLo = [\n        0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,\n        0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,\n        0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,\n        0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,\n        0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,\n        0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,\n        0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,\n        0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,\n        0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,\n        0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,\n        0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,\n        0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,\n        0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,\n        0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,\n        0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,\n        0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,\n        0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,\n        0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,\n        0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,\n        0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,\n        0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,\n        0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,\n        0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,\n        0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,\n        0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,\n        0x43, 0x83, 0x41, 0x81, 0x80, 0x40\n      ];\n\n//var data=Buffer.from([1,15,0,0,0,10,2,255,0,0,0]);\nvar data=Buffer.from(msg.payload);\nvar nTemp;\nvar wCRCWord = 0xFFFF;\n//data=msg.payload;\nvar len=data.length-2;\nvar crc = [0xFF, 0xFF];\n    var nextByte = 0;\n    var uIndex; /* will index into CRC lookup*/ /* table */\n    /* pass through message buffer */\n    for (var i = 0; i < len && i < data.length; i++) {\n      nextByte = 0xFF & (data[i]);\n      uIndex = crc[0] ^ nextByte; //*puchMsg++; /* calculate the CRC */\n      crc[0] = crc[1] ^ auchCRCHi[uIndex];\n      crc[1] = auchCRCLo[uIndex];\n    }\n\ndata[len]=crc[0];\ndata[len+1]=crc[1];\nmsg.payload= data;\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "x": 650,
        "y": 460,
        "wires": [
            [
                "a6458f925124e27f"
            ]
        ]
    },
    {
        "id": "7ac6f0a21739dc93",
        "type": "ui_group",
        "name": "LS산전 PLC",
        "tab": "97d176029c50b84f",
        "order": 1,
        "disp": true,
        "width": "6",
        "collapse": false
    },
    {
        "id": "63957752.49a888",
        "type": "serial-port",
        "serialport": "COM6",
        "serialbaud": "19200",
        "databits": "8",
        "parity": "none",
        "stopbits": "1",
        "waitfor": "",
        "dtr": "none",
        "rts": "none",
        "cts": "none",
        "dsr": "none",
        "newline": "100",
        "bin": "bin",
        "out": "time",
        "addchar": "",
        "responsetimeout": "10000"
    },
    {
        "id": "97d176029c50b84f",
        "type": "ui_tab",
        "name": "입출력 모니터",
        "icon": "dashboard",
        "order": 3,
        "disabled": false,
        "hidden": false
    }
]
```

### 2-27-3 node red program
node red에서 HTML로 plc를 제어한다.
```
[
    {
        "id": "b8ef731462eb3aac",
        "type": "template",
        "z": "7cebe1323521596f",
        "name": "style",
        "field": "payload.style",
        "fieldType": "msg",
        "format": "handlebars",
        "syntax": "mustache",
        "template": "body {\n    background: #eab0dc;\n    font-family: \"Lato\", sans-serif;\n}\n.button {\n    border: none;\n    border-color:black;\n    color: white;\n    padding: 20px;\n    text-align: center;\n    text-decoration: none;\n    display: inline-block;\n    font-size: 16px;\n    margin: 4px 2px;\n    cursor: pointer;\n}\n.buttonMenu {\n    padding: 5px 24px;\n    margin-left:20%;\n    background-color:black;\n    border: none;\n    border-color:black;\n    color:white;\n    text-align: left;\n    text-decoration: none;\n    display: inline-block;\n    font-size: 16px;\n    margin: 4px 2px;\n    cursor: pointer;\n}\n.sidenav {\n    height: 100%;\n    width: 0;\n    position: fixed;\n    z-index: 1;\n    top: 0;\n    left: 0;\n    background-color: #111;\n    overflow-x: hidden;\n    transition: 0.5s;\n    padding-top: 60px;\n}\n.sidenav a {\n    padding: 8px 8px 8px 32px;\n    text-decoration: none;\n    font-size: 18px;\n    color: #818181;\n    display: block;\n    transition: 0.3s;\n}\n.sidenav a:hover {\n    color: #f1f1f1;\n}\n\n.sidenav .closebtn {\n    position: absolute;\n    top: 0;\n    right: 25px;\n    font-size: 36px;\n    margin-left: 50px;\n}\n\n.button-on {border-radius: 100%; background-color: #4CAF50;}\n.button-off {border-radius: 100%;background-color: #707070;}\n.button-ledon {border-radius: 100%; padding: 10px; font-size: 8px; margin: 0px 0px; background-color: #ff4500;}\n.button-ledoff {border-radius: 100%; padding: 10px; font-size: 8px; background-color: #707070;}",
        "output": "str",
        "x": 330,
        "y": 180,
        "wires": [
            [
                "a5a2a89b2880760d"
            ]
        ]
    },
    {
        "id": "64932616a8af4e32",
        "type": "http in",
        "z": "7cebe1323521596f",
        "name": "",
        "url": "/main",
        "method": "get",
        "upload": false,
        "swaggerDoc": "",
        "x": 180,
        "y": 180,
        "wires": [
            [
                "b8ef731462eb3aac"
            ]
        ]
    },
    {
        "id": "9dc88b847f33feda",
        "type": "http response",
        "z": "7cebe1323521596f",
        "name": "",
        "statusCode": "",
        "headers": {},
        "x": 730,
        "y": 180,
        "wires": []
    },
    {
        "id": "7a4529daec00f680",
        "type": "template",
        "z": "7cebe1323521596f",
        "name": "",
        "field": "payload",
        "fieldType": "msg",
        "format": "handlebars",
        "syntax": "mustache",
        "template": "<!DOCTYPE html>\n<html>\n<head>\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n{{{payload.h}}}\n<style> {{{payload.style}}} </style>\n</head>\n<body>\n<h3 style='color:SteelBlue;'>&emsp;김동일유튜브 <a href='http://i2r.link' style='color:SteelBlue;'>http://i2r.link</a> </h3>\n<h3 style='color:SteelBlue;'>&emsp;4차산업혁명의 시작 -> 센서와 엑튜에이터를 크라우드컴퓨터 빅데이터에 연결</h3>\n{{{payload.t}}} \n</body>\n</html>",
        "output": "str",
        "x": 600,
        "y": 180,
        "wires": [
            [
                "9dc88b847f33feda"
            ]
        ]
    },
    {
        "id": "a5a2a89b2880760d",
        "type": "function",
        "z": "7cebe1323521596f",
        "name": "html 작성",
        "func": "global.set(\"style\",msg.payload.style);\nvar In = global.get('In') || \"\";\nvar out = global.get('out') || [0,0,0,0,0,0];\nvar monit = global.get('monit') || '0';\nvar s=\"\";\nvar i=0;\n\ns+=\"모니터링 \";\ns+=\"<form action='/on'>\";\ns+=\"<input type='hidden' name='act' value='1'>\";\ns+=\"<input type='hidden' name='no' value='0'>\";\nif(monit=='1') \n    s+=\"<th><button type='submit' name='value' value='0' class='button button-on' ></button></a></th>\";\nelse\n    s+=\"<th><button type='submit' name='value' value='1' class='button button-off' ></button></a></th>\";    \ns+=\"</form>\";\n\n\ns+=\"입력<br>\";\ns+=\"<table>\";\ns+=\"<tr>\";\ns+=\"<th>q00</th>\";\ns+=\"<th>q01</th>\";\ns+=\"<th>q02</th>\";\ns+=\"<th>q03</th>\";\ns+=\"<th>q04</th>\";\ns+=\"<th>q05</th>\";\ns+=\"<th>q06</th>\";\ns+=\"<th>q07</th>\";\ns+=\"</tr>\";\ns+=\"<tr>\";\nfor(i=0;i<8;i++) {\nif(In.charAt(7-i)=='1') \n    s+=\"<th><button type='submit' name='value' value='0' class='button button-ledon' ></button></a></th>\";\nelse\n    s+=\"<th><button type='submit' name='value' value='1' class='button button-ledoff' ></button></a></th>\";    \n}\ns+=\"</tr>\";\ns+=\"</table>\";\n\ns+=\"출력<br>\";\ns+=\"<table>\";\ns+=\"<tr>\";\ns+=\"<th>i00</th>\";\ns+=\"<th>i01</th>\";\ns+=\"<th>i02</th>\";\ns+=\"<th>i03</th>\";\ns+=\"<th>i04</th>\";\ns+=\"<th>i05</th>\";\ns+=\"</tr>\";\ns+=\"<tr>\";\nfor(i=0;i<6;i++) {\ns+=\"<form action='/on'>\";\ns+=\"<input type='hidden' name='act' value='0'>\";\ns+=\"<input type='hidden' name='no' value='\"+i.toString()+\"'>\";\nif(out[i]=='1') \n    s+=\"<th><button type='submit' name='value' value='0' class='button button-on' ></button></a></th>\";\nelse\n    s+=\"<th><button type='submit' name='value' value='1' class='button button-off' ></button></a></th>\";    \ns+=\"</form>\";\n}\ns+=\"</tr>\";\ns+=\"</table>\";\n\nmsg.payload.t=s;\nif(monit=='1')\n    msg.payload.h=\"<meta http-equiv='refresh' content='3; url='http://117.16.176.76:1880/main' method='get'>\";\nelse\n    msg.payload.h=\"\";\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 460,
        "y": 180,
        "wires": [
            [
                "7a4529daec00f680"
            ]
        ]
    },
    {
        "id": "bcd20a98ec98495f",
        "type": "function",
        "z": "7cebe1323521596f",
        "name": "디코드",
        "func": "var dec=msg.payload[3];\nvar bin = parseInt(dec).toString(2);\nbin=\"00000000\"+bin;\nbin = bin.slice(-8);\nglobal.set(\"In\",bin);\nmsg.payload=bin;\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 833,
        "y": 115,
        "wires": [
            []
        ]
    },
    {
        "id": "0b7a129b0248dcf1",
        "type": "function",
        "z": "7cebe1323521596f",
        "name": "입력포트 읽기",
        "func": "var monit = global.get('monit') || '0';\n\nif(monit != '0') {\n    buf=[1,2,0,0,0,8,0,0];\n    msg.payload=buf;\n    return msg;\n}",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 380,
        "y": 115,
        "wires": [
            [
                "930c70e396e0398c"
            ]
        ]
    },
    {
        "id": "930c70e396e0398c",
        "type": "function",
        "z": "7cebe1323521596f",
        "name": "modbus cal",
        "func": "var auchCRCHi = [\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40\n      ];\n\n      /* Table of CRC values for low-order byte */\n    var auchCRCLo = [\n        0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,\n        0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,\n        0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,\n        0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,\n        0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,\n        0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,\n        0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,\n        0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,\n        0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,\n        0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,\n        0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,\n        0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,\n        0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,\n        0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,\n        0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,\n        0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,\n        0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,\n        0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,\n        0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,\n        0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,\n        0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,\n        0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,\n        0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,\n        0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,\n        0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,\n        0x43, 0x83, 0x41, 0x81, 0x80, 0x40\n      ];\n\n//var data=Buffer.from([1,15,0,0,0,10,2,255,0,0,0]);\nvar data=Buffer.from(msg.payload);\nvar nTemp;\nvar wCRCWord = 0xFFFF;\n//data=msg.payload;\nvar len=data.length-2;\nvar crc = [0xFF, 0xFF];\n    var nextByte = 0;\n    var uIndex; /* will index into CRC lookup*/ /* table */\n    /* pass through message buffer */\n    for (var i = 0; i < len && i < data.length; i++) {\n      nextByte = 0xFF & (data[i]);\n      uIndex = crc[0] ^ nextByte; //*puchMsg++; /* calculate the CRC */\n      crc[0] = crc[1] ^ auchCRCHi[uIndex];\n      crc[1] = auchCRCLo[uIndex];\n    }\n\ndata[len]=crc[0];\ndata[len+1]=crc[1];\nmsg.payload= data;\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "x": 561.0000152587891,
        "y": 113.99998664855957,
        "wires": [
            [
                "f2d546c2eb364390"
            ]
        ]
    },
    {
        "id": "8061d305fc205d65",
        "type": "inject",
        "z": "7cebe1323521596f",
        "name": "",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "2",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payloadType": "date",
        "x": 210,
        "y": 115,
        "wires": [
            [
                "0b7a129b0248dcf1"
            ]
        ]
    },
    {
        "id": "f2d546c2eb364390",
        "type": "serial request",
        "z": "7cebe1323521596f",
        "name": "",
        "serial": "63957752.49a888",
        "x": 713,
        "y": 115,
        "wires": [
            [
                "bcd20a98ec98495f"
            ]
        ]
    },
    {
        "id": "340da80d3d452617",
        "type": "comment",
        "z": "7cebe1323521596f",
        "name": "참조메뉴얼",
        "info": "LS산전 \"사용설명서_XGB Cnet_V1.8.pdf\"\n9-8 페이지\n9.4.2 비트 입력영역에 비트형식의 데이터 읽기(02) ",
        "x": 180,
        "y": 75,
        "wires": []
    },
    {
        "id": "88b033eede885914",
        "type": "comment",
        "z": "7cebe1323521596f",
        "name": "참조유튜브",
        "info": "https://youtu.be/hlGKl6BQL78",
        "x": 340,
        "y": 75,
        "wires": []
    },
    {
        "id": "a51adc260471b9f0",
        "type": "http in",
        "z": "7cebe1323521596f",
        "name": "",
        "url": "/on",
        "method": "get",
        "upload": false,
        "swaggerDoc": "",
        "x": 180,
        "y": 260,
        "wires": [
            [
                "a56db3695addc8b2",
                "6feaf19209809869"
            ]
        ]
    },
    {
        "id": "9d25da4ae153225b",
        "type": "template",
        "z": "7cebe1323521596f",
        "name": "html",
        "field": "payload",
        "fieldType": "msg",
        "format": "handlebars",
        "syntax": "mustache",
        "template": "<html>\n    <head>\n        <meta name='viewport' content='width=device-width, initial-scale=1.0'/>\n        <meta http-equiv='refresh' content='0; url=http://192.168.0.3:1880/main' method='get'> \n    </head>\n    <body>\n       </body>\n</html",
        "output": "str",
        "x": 490,
        "y": 260,
        "wires": [
            [
                "6c20e754eca0841a"
            ]
        ]
    },
    {
        "id": "6c20e754eca0841a",
        "type": "http response",
        "z": "7cebe1323521596f",
        "name": "Go Main Page",
        "statusCode": "",
        "headers": {},
        "x": 642,
        "y": 260,
        "wires": []
    },
    {
        "id": "a56db3695addc8b2",
        "type": "function",
        "z": "7cebe1323521596f",
        "name": "act 처리",
        "func": "var out = global.get('out') || [0,0,0,0,0,0];\nvar monit = global.get('monit') || '0';\n\nif(msg.payload.act==0) {\n    out[msg.payload.no] = parseInt(msg.payload.value);\n    global.set('out',out);\n}\nelse if(msg.payload.act==1)\n   global.set(\"monit\",msg.payload.value);\n \nreturn msg;\n\n",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 340,
        "y": 260,
        "wires": [
            [
                "9d25da4ae153225b",
                "c9d6f4463fa5adfb"
            ]
        ]
    },
    {
        "id": "e19a2993c017b11d",
        "type": "serial out",
        "z": "7cebe1323521596f",
        "name": "",
        "serial": "63957752.49a888",
        "x": 770,
        "y": 320,
        "wires": []
    },
    {
        "id": "3af7565842774599",
        "type": "function",
        "z": "7cebe1323521596f",
        "name": "modbus cal",
        "func": "var auchCRCHi = [\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,\n        0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,\n        0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,\n        0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,\n        0x80, 0x41, 0x00, 0xC1, 0x81, 0x40\n      ];\n\n      /* Table of CRC values for low-order byte */\n    var auchCRCLo = [\n        0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,\n        0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,\n        0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,\n        0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,\n        0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,\n        0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,\n        0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,\n        0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,\n        0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,\n        0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,\n        0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,\n        0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,\n        0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,\n        0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,\n        0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,\n        0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,\n        0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,\n        0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,\n        0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,\n        0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,\n        0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,\n        0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,\n        0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,\n        0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,\n        0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,\n        0x43, 0x83, 0x41, 0x81, 0x80, 0x40\n      ];\n\n//var data=Buffer.from([1,15,0,0,0,10,2,255,0,0,0]);\nvar data=Buffer.from(msg.payload);\nvar nTemp;\nvar wCRCWord = 0xFFFF;\n//data=msg.payload;\nvar len=data.length-2;\nvar crc = [0xFF, 0xFF];\n    var nextByte = 0;\n    var uIndex; /* will index into CRC lookup*/ /* table */\n    /* pass through message buffer */\n    for (var i = 0; i < len && i < data.length; i++) {\n      nextByte = 0xFF & (data[i]);\n      uIndex = crc[0] ^ nextByte; //*puchMsg++; /* calculate the CRC */\n      crc[0] = crc[1] ^ auchCRCHi[uIndex];\n      crc[1] = auchCRCLo[uIndex];\n    }\n\ndata[len]=crc[0];\ndata[len+1]=crc[1];\nmsg.payload= data;\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "x": 630,
        "y": 320,
        "wires": [
            [
                "e19a2993c017b11d"
            ]
        ]
    },
    {
        "id": "c9d6f4463fa5adfb",
        "type": "function",
        "z": "7cebe1323521596f",
        "name": "쓰기",
        "func": "var out = global.get('out') || [0,0,0,0,0,0];\nvar buf = Buffer.alloc(11);\nbuf=[1,15,0,64,0,10,2,255,0,0,0];\n//buf[7]=i00*1+i01*2+i02*4+i03*8+i04*16+i05*32;\nbuf[7]=out[0]*1+out[1]*2+out[2]*4+out[3]*8+out[4]*16+out[5]*32;\n\nmsg.payload=buf;\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 490,
        "y": 320,
        "wires": [
            [
                "3af7565842774599"
            ]
        ]
    },
    {
        "id": "6feaf19209809869",
        "type": "debug",
        "z": "7cebe1323521596f",
        "name": "",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "statusVal": "",
        "statusType": "auto",
        "x": 380,
        "y": 400,
        "wires": []
    },
    {
        "id": "63957752.49a888",
        "type": "serial-port",
        "serialport": "COM6",
        "serialbaud": "19200",
        "databits": "8",
        "parity": "none",
        "stopbits": "1",
        "waitfor": "",
        "dtr": "none",
        "rts": "none",
        "cts": "none",
        "dsr": "none",
        "newline": "100",
        "bin": "bin",
        "out": "time",
        "addchar": "",
        "responsetimeout": "10000"
    }
]
```
# 2-27-4 구글 음성을 이용한 PLC 제어
구글 다이어로그에서 "1번 켜" 하면 plc에서 출력이 나간다.    
"FirebaseESP8266.h"의 라이브러리 "Firebase ESP8266 Client"는 2.9.0 버젼을 선택한다.

index.js
```
//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include "CRC.h"

SoftwareSerial mySerial(D7, D4); // RX, TX

#define FIREBASE_HOST "***.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "***"
#define WIFI_SSID "i2r"
#define WIFI_PASSWORD "00000000"

//Define FirebaseESP8266 data object
FirebaseData firebaseData1;
FirebaseData firebaseData2;

unsigned long sendDataPrevMillis = 0;

String path = "/data";

uint16_t count = 0;

int outPlc=1;
//unsigned long previousMillis = 0;   
//const long interval = 3000; 
String inputString = "";         // 받은 문자열
int Out[8]={0,0,0,0},In[10]={0};  // plc 입력과 출력 저장 

void printResult(FirebaseData &data);
void printResult(StreamData &data);
void outResult(StreamData &data);

void streamCallback(StreamData data)
{

  Serial.println("Stream Data1 available...");
  Serial.println("STREAM PATH: " + data.streamPath());
  Serial.println("EVENT PATH: " + data.dataPath());
  Serial.println("DATA TYPE: " + data.dataType());
  Serial.println("EVENT TYPE: " + data.eventType());
  Serial.print("VALUE: ");
  printResult(data);
  Serial.println();
  outResult(data);
}

void streamTimeoutCallback(bool timeout)
{
  if (timeout)
  {
    Serial.println();
    Serial.println("Stream timeout, resume streaming...");
    Serial.println();
  }
}

void setup()
{
  Serial.begin(19200);
  mySerial.begin(19200);
  Serial.println("start");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  firebaseData1.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  firebaseData1.setResponseSize(1024);


  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  firebaseData2.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  firebaseData2.setResponseSize(1024);



  if (!Firebase.beginStream(firebaseData1, path))
  {
    Serial.println("------------------------------------");
    Serial.println("Can't begin stream connection...");
    Serial.println("REASON: " + firebaseData1.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  Firebase.setStreamCallback(firebaseData1, streamCallback, streamTimeoutCallback);
}

void loop()
{

}

// 아두이노에서 RS485 출력을 내보낸다.
void crd16Rtu() {
  String s;
  int si,sj,len;
  char str[24];

  if(outPlc == 1) {  //출력
    //str[24] =  {0x01,0x0f,0x00,0x00,0x00,0x0a,0x02,0xff,0x00,0x00,0x00};  //비트연속출력 len=9
    str[0]=0x01; str[1]=0x0f; str[2]=0x00; str[3]=0x00; str[4]=0x00;
    str[5]=0x0a; str[6]=0x02; str[7]=0xff; str[8]=0x00; str[9]=0x00; str[10]=0x00;
    len=9;
    str[7]=Out[0]+Out[1]*2+Out[2]*4+Out[3]*8+Out[4]*16+Out[5]*32;
    outPlc=0;
  }
  else {    //입력
    //str[24] =  {0x01,0x02,0x00,0x00,0x00,0x08,0x00,0x00}; // 비트 입력영역 읽기 len=6
    str[0]=0x01; str[1]=0x02; str[2]=0x00; str[3]=0x00; str[4]=0x00;
    str[5]=0x08; str[6]=0x00; str[7]=0x00; 
    len=6;
  }

  inputString = "";
  uint8_t * data = (uint8_t *) &str[0];
  si=crc16(data, len, 0x8005, 0xFFFF, 0x0000, true,  true  );
  sj=si&0xff;
  str[len]=sj;
  sj=si>>8;
  str[len+1]=sj;

  for(int i=0;i<len+2;i++)
    mySerial.print(str[i]);
}

void printResult(FirebaseData &data)
{

  if (data.dataType() == "int")
    Serial.println(data.intData());
  else if (data.dataType() == "float")
    Serial.println(data.floatData(), 5);
  else if (data.dataType() == "double")
    printf("%.9lf\n", data.doubleData());
  else if (data.dataType() == "boolean")
    Serial.println(data.boolData() == 1 ? "true" : "false");
  else if (data.dataType() == "string")
    Serial.println(data.stringData());
  else if (data.dataType() == "json")
  {
    Serial.println();
    FirebaseJson &json = data.jsonObject();
    //Print all object data
    Serial.println("Pretty printed JSON data:");
    String jsonStr;
    json.toString(jsonStr, true);
    Serial.println(jsonStr);
    Serial.println();
    Serial.println("Iterate JSON data:");
    Serial.println();
    size_t len = json.iteratorBegin();
    String key, value = "";
    int type = 0;
    for (size_t i = 0; i < len; i++)
    {
      json.iteratorGet(i, type, key, value);
      Serial.print(i);
      Serial.print(", ");
      Serial.print("Type: ");
      Serial.print(type == FirebaseJson::JSON_OBJECT ? "object" : "array");
      if (type == FirebaseJson::JSON_OBJECT)
      {
        Serial.print(", Key: ");
        Serial.print(key);
      }
      Serial.print(", Value: ");
      Serial.println(value);
    }
    json.iteratorEnd();
  }
  else if (data.dataType() == "array")
  {
    Serial.println();
    //get array data from FirebaseData using FirebaseJsonArray object
    FirebaseJsonArray &arr = data.jsonArray();
    //Print all array values
    Serial.println("Pretty printed Array:");
    String arrStr;
    arr.toString(arrStr, true);
    Serial.println(arrStr);
    Serial.println();
    Serial.println("Iterate array values:");
    Serial.println();
    for (size_t i = 0; i < arr.size(); i++)
    {
      Serial.print(i);
      Serial.print(", Value: ");

      FirebaseJsonData &jsonData = data.jsonData();
      //Get the result data from FirebaseJsonArray object
      arr.get(jsonData, i);
      if (jsonData.typeNum == FirebaseJson::JSON_BOOL)
        Serial.println(jsonData.boolValue ? "true" : "false");
      else if (jsonData.typeNum == FirebaseJson::JSON_INT)
        Serial.println(jsonData.intValue);
      else if (jsonData.typeNum == FirebaseJson::JSON_DOUBLE)
        printf("%.9lf\n", jsonData.doubleValue);
      else if (jsonData.typeNum == FirebaseJson::JSON_STRING ||
               jsonData.typeNum == FirebaseJson::JSON_NULL ||
               jsonData.typeNum == FirebaseJson::JSON_OBJECT ||
               jsonData.typeNum == FirebaseJson::JSON_ARRAY)
        Serial.println(jsonData.stringValue);
    }
  }
}

void printResult(StreamData &data)
{

  if (data.dataType() == "int")
    Serial.println(data.intData());
  else if (data.dataType() == "float")
    Serial.println(data.floatData(), 5);
  else if (data.dataType() == "double")
    printf("%.9lf\n", data.doubleData());
  else if (data.dataType() == "boolean")
    Serial.println(data.boolData() == 1 ? "true" : "false");
  else if (data.dataType() == "string")
    Serial.println(data.stringData());
  else if (data.dataType() == "json")
  {
    Serial.println();
    FirebaseJson *json = data.jsonObjectPtr();
    //Print all object data
    Serial.println("Pretty printed JSON data:");
    String jsonStr;
    json->toString(jsonStr, true);
    Serial.println(jsonStr);
    Serial.println();
    Serial.println("Iterate JSON data:");
    Serial.println();
    size_t len = json->iteratorBegin();
    String key, value = "";
    int type = 0;
    for (size_t i = 0; i < len; i++)
    {
      json->iteratorGet(i, type, key, value);
      Serial.print(i);
      Serial.print(", ");
      Serial.print("Type: ");
      Serial.print(type == FirebaseJson::JSON_OBJECT ? "object" : "array");
      if (type == FirebaseJson::JSON_OBJECT)
      {
        Serial.print(", Key: ");
        Serial.print(key);
      }
      Serial.print(", Value: ");
      Serial.println(value);
    }
    json->iteratorEnd();
  }
  else if (data.dataType() == "array")
  {
    Serial.println();
    //get array data from FirebaseData using FirebaseJsonArray object
    FirebaseJsonArray *arr = data.jsonArrayPtr();
    //Print all array values
    Serial.println("Pretty printed Array:");
    String arrStr;
    arr->toString(arrStr, true);
    Serial.println(arrStr);
    Serial.println();
    Serial.println("Iterate array values:");
    Serial.println();

    for (size_t i = 0; i < arr->size(); i++)
    {
      Serial.print(i);
      Serial.print(", Value: ");

      FirebaseJsonData *jsonData = data.jsonDataPtr();
      //Get the result data from FirebaseJsonArray object
      arr->get(*jsonData, i);
      if (jsonData->typeNum == FirebaseJson::JSON_BOOL)
        Serial.println(jsonData->boolValue ? "true" : "false");
      else if (jsonData->typeNum == FirebaseJson::JSON_INT)
        Serial.println(jsonData->intValue);
      else if (jsonData->typeNum == FirebaseJson::JSON_DOUBLE)
        printf("%.9lf\n", jsonData->doubleValue);
      else if (jsonData->typeNum == FirebaseJson::JSON_STRING ||
               jsonData->typeNum == FirebaseJson::JSON_NULL ||
               jsonData->typeNum == FirebaseJson::JSON_OBJECT ||
               jsonData->typeNum == FirebaseJson::JSON_ARRAY)
        Serial.println(jsonData->stringValue);
    }
  }
}

void outResult(StreamData &data)
{
  int onValue=1;
  int noPlc=0;
  if (data.dataType() == "int")
    onValue=data.intData();
  else if (data.dataType() == "string") {
    if(data.stringData() != "1")
      onValue=0;
    Serial.println(data.stringData());
  }
  else if (data.dataType() == "json")
  {
    FirebaseJson *json = data.jsonObjectPtr();
    String jsonStr;
    json->toString(jsonStr, true);

    FirebaseJsonData jsonObj;
    json->get(jsonObj,"on");
    onValue=jsonObj.intValue;
    json->get(jsonObj,"no");
    noPlc=jsonObj.intValue;
    Out[noPlc]=onValue;
    crd16Rtu();
  }
}
```


