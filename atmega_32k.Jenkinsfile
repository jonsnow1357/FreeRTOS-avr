pipeline {
  agent any

  //environment {
  //  BUILD_EMAIL_TO = ""
  //  BUILD_EMAIL_BODY = """build info: ${env.BUILD_URL}"""
  //}

  options {
    [
    buildDiscarder(logRotator(artifactDaysToKeepStr: "", artifactNumToKeepStr: "", daysToKeepStr: "", numToKeepStr: "8")),
    disableConcurrentBuilds(),
    pipelineTriggers([cron('16 H * * *')]),
    //pipelineTriggers([pollSCM('H/30 * * * *')])
    ],
  }

  parameters {
    choice(name: "AVR_FR_OPT", choices: ["old", "new"], description: "FreeRTOS AVR port")
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
        catchError(buildResult: "FAILURE", stageResult: "FAILURE") {
          sh "mkdir -p build; cd build; rm -rvf *; cmake -DAVR_MCU=atmega32 -DAVR_FR_OPT=${params.AVR_FR_OPT} ..; make;"
        }
      }
    }
    stage ("atmega32a") {
      steps {
        catchError(buildResult: "FAILURE", stageResult: "FAILURE") {
          sh "mkdir -p build; cd build; rm -rvf *; cmake -DAVR_MCU=atmega32a -DAVR_FR_OPT=${params.AVR_FR_OPT} ..; make;"
        }
      }
    }
    stage ("atmega32u2") {
      steps {
        catchError(buildResult: "FAILURE", stageResult: "FAILURE") {
          sh "mkdir -p build; cd build; rm -rvf *; cmake -DAVR_MCU=atmega32u2 -DAVR_FR_OPT=${params.AVR_FR_OPT} ..; make;"
        }
      }
    }
    stage ("atmega323") {
      steps {
        catchError(buildResult: "FAILURE", stageResult: "FAILURE") {
          sh "mkdir -p build; cd build; rm -rvf *; cmake -DAVR_MCU=atmega323 -DAVR_FR_OPT=${params.AVR_FR_OPT} ..; make;"
        }
      }
    }
  }

  post {
    always {
      junit allowEmptyResults: true, testResults: "test.xml"
    }
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
