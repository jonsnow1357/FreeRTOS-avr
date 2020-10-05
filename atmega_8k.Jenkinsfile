pipeline {
  agent any

  //environment {
  //  BUILD_EMAIL_TO = ""
  //  BUILD_EMAIL_BODY = """build info: ${env.BUILD_URL}"""
  //}

  triggers {
    pollSCM ("H/30 * * * *")
  }

  stages {
    stage ("env") {
      steps {
        sh "env"
      }
    }
    stage ("extra SCM") {
      steps {
        checkout([$class: 'GitSCM', branches: [[name: '*/master']], doGenerateSubmoduleConfigurations: false,
                  extensions: [[$class: 'RelativeTargetDirectory', relativeTargetDir: 'FreeRTOS-Kernel'], [$class: 'CleanCheckout']],
                  submoduleCfg: [],
                  userRemoteConfigs: [[url: 'https://github.com/jonsnow1357/FreeRTOS-Kernel.git']]
        ])
      }
    }
    stage ("atmega32") {
      steps {
        sh "mkdir -p build; cd build; rm -rvf *; cmake -DAVR_MCU=atmega32 ..; make;"
      }
    }
    stage ("atmega8") {
      steps {
        sh "mkdir -p build; cd build; rm -rvf *; cmake -DAVR_MCU=atmega8 ..; make;"
      }
    }
    stage ("atmega8a") {
      steps {
        sh "mkdir -p build; cd build; rm -rvf *; cmake -DAVR_MCU=atmega8a ..; make;"
      }
    }
    //stage ("atmega8hva") {
    //  steps {
    //    sh "mkdir -p build; cd build; rm -rvf *; cmake -DAVR_MCU=atmega8hva ..; make;"
    //  }
    //}
    stage ("atmega8u2") {
      steps {
        sh "mkdir -p build; cd build; rm -rvf *; cmake -DAVR_MCU=atmega8u2 ..; make;"
      }
    }
    stage ("atmega8515") {
      steps {
        sh "mkdir -p build; cd build; rm -rvf *; cmake -DAVR_MCU=atmega8515 ..; make;"
      }
    }
    stage ("atmega8535") {
      steps {
        sh "mkdir -p build; cd build; rm -rvf *; cmake -DAVR_MCU=atmega8535 ..; make;"
      }
    }
  }

  post {
    //always {
    //  junit allowEmptyResults: true, testResults: "${PY_MODULE}/tests/data_out/test_py*.xml"
    //}
    //failure {
    //  emailext (
    //    subject: "FAILURE: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'",
    //    body: "${BUILD_EMAIL_BODY}",
    //    to: "${BUILD_EMAIL_TO}"
    //  )
    //}
    //aborted {
    //  emailext (
    //    subject: "ABORTED: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'",
    //    body: "${BUILD_EMAIL_BODY}",
    //    to: "${BUILD_EMAIL_TO}"
    //  )
    //}
    //unstable {
    //  emailext (
    //    subject: "UNSTABLE: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'",
    //    body: "${BUILD_EMAIL_BODY}",
    //    to: "${BUILD_EMAIL_TO}"
    //  )
    //}
    cleanup{
      deleteDir()
    }
  }
}
